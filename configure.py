import argparse
from dataclasses import dataclass
import io
import json
import os
from pathlib import Path
import shutil
import struct
import subprocess
import sys
import yaml

import ninja_syntax
from elftools.elf.elffile import ELFFile
import rabbitizer
import splat
import splat.scripts.split as split
from splat.segtypes.linker_entry import LinkerEntry

ROOT        = Path(__file__).parent.resolve()
TOOLS_DIR   = ROOT / "tools"
CLEAN_FILES = [".splache", ".ninja_log", "build.ninja", "MAIN.ELF.ld", "permuter_settings.toml", "compile_commands.json", "objdiff.json"]
CLEAN_DIRS  = ["asm", "assets", "build"]

CROSS              = "mips-linux-gnu"
COMPILER_ID        = "ee-gcc"
COMPILER_VER       = "2.9-991111-01"
COMPILER_DIR       = f"{TOOLS_DIR}/cc/{COMPILER_ID}{COMPILER_VER}"
COMMON_INCLUDES    = f"-Iinclude -Isrc -isystem lib/ee -isystem lib -isystem {COMPILER_DIR}/ee/include -isystem {COMPILER_DIR}/lib/gcc-lib/ee/2.9-ee-991111-01/include"
COMPILER_FLAGS_C   = "-O1 -G8 -gstabs -fno-common"
COMPILER_FLAGS_CPP = "-O2 -G8 -gstabs -x c++ -fno-exceptions -fno-common"
COMPILE_CMD_C      = f"{COMPILER_DIR}/bin/ee-gcc -c {COMMON_INCLUDES} {COMPILER_FLAGS_C}"
COMPILE_CMD_CPP    = f"{COMPILER_DIR}/bin/ee-gcc -c {COMMON_INCLUDES} {COMPILER_FLAGS_CPP}"

# TODO: delete this
SECTION_ADDRS = {
    "vutext": 0x1E1900,
    "vudata": 0x253000,
    # "rodata": 0x260F00,
    "rodata": 0x369A58 - 0x100000 + 0x1000,
    "gcc_except_table": 0x271400,
    # "lit4": 0x271500,
    "sbss": 0x276800,
    "bss": 0x276864
}

SECTION_TYPE = {
    "vutext": "data",
    "vudata": "data",
    "rodata": "rodata",
    "gcc_except_table": "rodatabin",
    "lit4": "lit4",
    "sbss": "sbss",
    "bss": "bss"
}

class HexInt(int): ...
def representer(dumper, data): return yaml.ScalarNode('tag:yaml.org,2002:int', f"0x{data:06X}")
yaml.add_representer(HexInt, representer)

class MyDumper(yaml.Dumper):
    def increase_indent(self, flow=False, indentless=False):
        return super(MyDumper, self).increase_indent(flow, False)

@dataclass
class Function:
    name: str
    address: int

    def dump(self) -> dict:
        return {
            "name": self.name,
            "address": HexInt(self.address)
        }
    
    @staticmethod
    def representer(dumper, data: "Function"):
        return yaml.SequenceNode(
            "tag:yaml.org,2002:seq",
            [
                yaml.ScalarNode("tag:yaml.org,2002:int", f"0x{data.address:08X}"),
                yaml.ScalarNode("tag:yaml.org,2002:str", data.name)
            ],
            flow_style=True
        )

@dataclass
class Data:
    name: str | None
    address: int
    section: str
    size: int

    def dump(self) -> dict:
        return {
            "name": self.name,
            "address": HexInt(self.address),
            "section": self.section,
            "size": HexInt(self.size)
        }

    @staticmethod
    def representer(dumper, data: "Data"):
        return yaml.SequenceNode(
            "tag:yaml.org,2002:seq",
            [
                yaml.ScalarNode("tag:yaml.org,2002:int", f"0x{data.address:08X}"),
                yaml.ScalarNode("tag:yaml.org,2002:str", data.name) if data.name is not None else yaml.ScalarNode("tag:yaml.org,2002:null", "null"),
                yaml.ScalarNode("tag:yaml.org,2002:str", data.section),
                yaml.ScalarNode("tag:yaml.org,2002:int", f"0x{data.size:04X}")
            ],
            flow_style=True
        )
    

@dataclass
class Unit:
    name: str
    functions: list[Function]
    data: list[Data]

    def dump(self) -> dict:
        d = { "name": self.name }
        if self.functions:
            d["functions"] = self.functions
        if self.data:
            d["data"] = self.data
        return d
    
    def get_section_start(self, section: str) -> Data | None:
        arr = [data for data in self.data if data.section == section]
        return min(arr, key=lambda x: x.address) if arr else None


@dataclass
class Section:
    id: str
    path: str
    units: list[Unit]

    def dump(self) -> dict:
        return {
            "id": self.id,
            "path": self.path,
            "units": [unit.dump() for unit in self.units]
        }

@dataclass
class SplatSegment:
    start: int
    type: str | None
    name: str | None
    vram: int | None = None

    @staticmethod
    def representer(dumper, data: "SplatSegment"):
        return yaml.SequenceNode(
            "tag:yaml.org,2002:seq",
            [
                yaml.ScalarNode("tag:yaml.org,2002:int", f"0x{data.start:06X}"),
                yaml.ScalarNode("tag:yaml.org,2002:str", data.type),
                yaml.ScalarNode("tag:yaml.org,2002:str", data.name),
            ] if data.name is not None else
            [
                yaml.ScalarNode("tag:yaml.org,2002:int", f"0x{data.start:06X}"),
                yaml.ScalarNode("tag:yaml.org,2002:str", data.type),
            ] if data.type is not None else
            [
                yaml.ScalarNode("tag:yaml.org,2002:int", f"0x{data.start:06X}"),
            ],
            flow_style=True
        ) if data.vram is None else yaml.MappingNode(
            "tag:yaml.org,2002:map",
            [
                (yaml.ScalarNode("tag:yaml.org,2002:str", "start"), yaml.ScalarNode("tag:yaml.org,2002:int", f"0x{data.start:06X}")),
                (yaml.ScalarNode("tag:yaml.org,2002:str", "type"), yaml.ScalarNode("tag:yaml.org,2002:str", data.type)),
                (yaml.ScalarNode("tag:yaml.org,2002:str", "vram"), yaml.ScalarNode("tag:yaml.org,2002:int", f"0x{data.vram:06X}")),
                (yaml.ScalarNode("tag:yaml.org,2002:str", "name"), yaml.ScalarNode("tag:yaml.org,2002:str", data.name)),
            ],
            flow_style=True
        )

yaml.add_representer(Function, Function.representer)
yaml.add_representer(Data, Data.representer)
yaml.add_representer(SplatSegment, SplatSegment.representer)

def get_gp_value(elf: ELFFile) -> int:
    text_section = elf.get_section_by_name(".text")
    text_data = text_section.data()
    registers = {"zero": 0}
    for i in range(32):
        word = struct.unpack("<i", text_data[i * 4:(i + 1) * 4])[0]
        instr = rabbitizer.Instruction(word)
        if instr.canBeHi() or instr.canBeLo() or instr.maybeIsMove():
            if instr.rt.name not in registers:
                registers[instr.rt.name] = 0
            match instr.getOpcodeName():
                case "lui":
                    registers[instr.rt.name] = instr.getProcessedImmediate() << 16
                case "addiu":
                    registers[instr.rt.name] = registers[instr.rs.name] + instr.getProcessedImmediate()
                case "daddu":
                    registers[instr.rd.name] = registers[instr.rs.name] + registers[instr.rt.name]
                case _:
                    raise Exception(f"Unknown instruction {instr}")
        if "gp" in registers:
            break
    if "gp" not in registers:
        raise Exception("Could not find $gp value")
    return registers.get("gp")

# this will be removed eventually
def create_paruu_config(elf: ELFFile, stdump: dict) -> list[Section]:
    text_section = elf.get_section_by_name(".text")
    lit4_section = elf.get_section_by_name(".lit4")
    text_data = text_section.data()
    lit4_range = (lit4_section.header.sh_addr, lit4_section.header.sh_addr + lit4_section.header.sh_size)
    
    gp_value = get_gp_value(elf)
    sections: dict[str, Section] = {}
    duplicates: dict[str, list[Function | Data]] = {}
    lib_section = Section("lib", "lib", [])
    lib_unit = Unit("sdk", [], [])
    lib_section.units.append(lib_unit)
    for source_file in stdump["source_files"]:
        source_file_split: str = source_file["name"].split("/home/hoshino/trial/src/")
        if len(source_file_split) == 1:
            section = lib_section
            unit = lib_unit
        else:
            source_file_dir = "/".join(source_file_split[1].split("/")[:-1])
            source_file_unit = source_file_split[1].split("/")[-1]
            source_file_lang = source_file_unit.split(".")[-1]
            section_id = f"{source_file_dir}:{source_file_lang}"
            if section_id not in sections:
                section = Section(section_id, section_id.split(":")[0], [])
                sections[section_id] = section
            else:
                section = sections[section_id]
            unit = Unit(source_file_unit, [], [])
            section.units.append(unit)

        for global_variable in map(lambda x: stdump["global_variables"][x], source_file.get("global_variables", [])):
            data = Data(global_variable["name"], global_variable["address"], global_variable["storage"]["location"], global_variable.get("size", 0))
            unit.data.append(data)

            if data.name not in duplicates:
                duplicates[data.name] = []
            duplicates[data.name].append(data)

        lit4_check = False
        for function in map(lambda x: stdump["functions"][x], source_file.get("functions", [])):
            func = Function(function["name"], function["address"])
            unit.functions.append(func)
            if func.name not in duplicates:
                duplicates[func.name] = []
            duplicates[func.name].append(func)

            if not lit4_check:
                func_addr = func.address - text_section.header.sh_addr
                func_words = struct.unpack(f"<{function["size"] // 4}i", text_data[func_addr:func_addr + function["size"]])
                for word in func_words:
                    instr = rabbitizer.Instruction(word)
                    if instr.getOpcodeName() == "lwc1" and instr.rs.name == "gp":
                        load_address = gp_value + instr.getProcessedImmediate()
                        if lit4_range[0] <= load_address < lit4_range[1]:
                            data = Data(None, load_address, "lit4", 0)
                            unit.data.append(data)
                            lit4_check = True
                            break

            for local_variable in map(lambda x: stdump["local_variables"][x], function.get("local_variables", [])):
                if local_variable["storage"]["type"] not in {"register", "stack"}:
                    data = Data(local_variable["name"], local_variable["address"], local_variable["storage"]["location"], local_variable.get("size", 0))
                    unit.data.append(data)

                    if data.name not in duplicates:
                        duplicates[data.name] = []
                    duplicates[data.name].append(data)
    
    sections["lib"] = lib_section

    SDATA_FIX = {
        "abe:c": {
            "ab_menu.c": 0x373B08,
            "firetest.c": 0x373B40,
        },
        "harada:c": {
            "hr_main.c": 0x373B60,
            "hr_mapv.c": 0x373C90
        },
        "hoshino:c": {
            "h_func.c": 0x374158,
            "h_menu.c": 0x374174,
            "h_test.c": 0x374198,
            "h_test_se.c": 0x374208,
            "h_util.c": 0x3743A8,
        },
        "kazuya:c": {
            "bios.c": 0x3743D8
        },
        "nakano:c": {
            "camera.c": 0x374AE0,
            "map01.c": 0x374BB8
        },
        "take:c": {
            "t_func.c": 0x375278,
            "view.c": 0x3752E8
        },
        "vtusr:c": {
            "vttmpprog.c": 0x375360
        }
    }

    RODATA_FIX = {
        "abe:c": {
            "ab_menu.c": 0x35FF00,
            "firetest.c": 0x35FF30,
            "sample.c": 0x35FF40
        },
        "harada:c": {
            "hr_bgwk.c": 0x35FFA0,
            "hr_main.c": 0x35FFC8,
            "hr_mapdr.c": 0x3603C0,
            "hr_mapv.c": 0x3603F0,
            "hr_mirr.c": 0x360A10,
            "hr_obcon.c": 0x360A40,
            "hr_obcon2.c": 0x360A60,
            "hr_obcon3.c": 0x360AF0,
            "hr_pall.c": 0x360CD8,
            "hr_pbgm.c": 0x360D68,
            "hr_pcam.c": 0x360DA0,
            "hr_pefc.c": 0x360E08,
            "hr_pmes.c": 0x360E20,
            "hr_pread.c": 0x360FE0,
            "hr_pream.c": 0x361078,
            "hr_prm.c": 0x361098,
            "hr_take.c": 0x361258,
            "hr_vpa.c": 0x3612A0,
            "hr_vpov.c": 0x3612E0,
            "hrmenu.c": 0x3613B0
        },
        "hato:c": {
            "ht_b01deb.c": 0x361410,
            "ht_b02deb.c": 0x3618E0,
            "ht_b03deb.c": 0x361C30,
            "ht_b04deb.c": 0x361F70,
            "ht_b06deb.c": 0x362310,
            "ht_b07deb.c": 0x362D20,
            "ht_b08deb.c": 0x362FF0,
            "ht_bcommon.c": 0x363110,
            "ht_bdraw.c": 0x3631F0,
            "ht_boss01.c": 0x3632B0,
            "ht_boss06.c": 0x363348,
            "ht_boss07.c": 0x3633E8,
            "ht_gbl.c": 0x3635A8,
            "ht_gimm.c": 0x3635F0,
            "ht_menu.c": 0x363638,
            "ht_meta.c": 0x363650,
            "ht_tat.c": 0x363790,
            "ht_tat2.c": 0x3637B0,
            "ht_zako.c": 0x363890
        },
        "hoshino:c": {
            "h_cdvd.c": 0x3638E0,
            "h_event.c": 0x3639C0,
            "h_file.c": 0x363A48,
            "h_game.c": 0x363A70,
            "h_gamesnd.c": 0x363D18,
            "h_init.c": 0x363E58,
            "h_menu.c": 0x364028,
            "h_rpc.c": 0x364048,
            "h_sound.c": 0x364060,
            "h_str.c": 0x364180,
            "h_test.c": 0x364210,
            "h_test_se.c": 0x364508,
            "h_util.c": 0x364608
        },
        "kazuya:c": {
            "bios.c": 0x364660,
            "menu.c": 0x364760,
            "obj_klo.c": 0x364780,
            "obj_std.c": 0x003647C8,
            "sample.c": 0x3647E8,
            "td_fljob.c": 0x364890,
            "td_job.c": 0x364920,
            "td_mhjob.c": 0x364970,
            "td_nejob.c": 0x364988,
            "td_sys.c": 0x3649A0,
            "wm_job.c": 0x3649C0,
            "wm_main.c": 0x364AF0
        },
        "nakano:c": {
            "camera.c": 0x364B80,
            "capture.c": 0x364D68,
            "dma.c": 0x364DE0,
            "filter.c": 0x364E30,
            "game.c": 0x364F10,
            "gflow.c": 0x365040,
            "gmiss.c": 0x365050,
            "ocamtst.c": 0x365BA0,
            "popuka.c": 0x365BE0,
            "route.c": 0x365D00,
            "rtconn.c": 0x365D10,
            "sinit.c": 0x365D30
        },
        "take:c": {
            "outline.c": 0x3695C8,
            "sfxbios.c": 0x3695E8,
            "t_sample.c": 0x369620,
            "title.c": 0x369668
        },
        "hoshino/kit:c": {
            "kitoutlinefunc.c": 0x369A38
        },
    }

    DATA_FIX = {
        "nakano:c": {
            "k_math.c": 0x304050
        },
        "take:c": {
            "motip.c": 0x329FF0
        }
    }

    for section, units in SDATA_FIX.items():
        for unit, address in units.items():
            next(u for u in sections[section].units if u.name == unit).data.append(Data(None, address, "sdata", 0))
    
    for section, units in RODATA_FIX.items():
        for unit, address in units.items():
            next(u for u in sections[section].units if u.name == unit).data.append(Data(None, address, "rodata", 0))

    for section, units in DATA_FIX.items():
        for unit, address in units.items():
            next(u for u in sections[section].units if u.name == unit).data.append(Data(None, address, "data", 0))
    
    for section in sections.values():
        for unit in section.units:
            unit.functions.sort(key=lambda x: x.address)
            unit.data.sort(key=lambda x: x.address)

    for name, things in duplicates.items():
        if len(things) > 1:
            for i, thing in enumerate(things):
                thing.name = f"{thing.name}.{i}"
    
    return list(sections.values())

def write_paruu_config(version: str, sections: list[Section]):
    with open(f"config/{version}/paruu.yml", "w") as f:
        paruu_config = {
            "id": "lv",
            "version": "trial",
            "name": "Klonoa 2: Lunatea's Veil (Demo Disc 2.3 Trial)",
            "platform": "ps2",
            "repository": "https://github.com/entriphy/kl2_lv_decomp",
            "src": "src",
            "basename": "MAIN.ELF",
            "debug": True,
            "sections": [section.dump() for section in sections]
        }
        yaml.dump(paruu_config, f, sort_keys=False, Dumper=MyDumper, default_flow_style=False)

def write_symbol_addrs(version: str, sections: list[Section], elf: ELFFile, stdump: dict):
    with open(f"config/{version}/symbol_addrs.txt", "w") as f:
        for section in sections:
            f.write(f"// -- {section.id} --\n\n")
            for unit in section.units:
                f.write(f"// {section.path}/{unit.name}\n")
                for function in unit.functions:
                    f.write(f"{function.name:<32} = 0x{function.address:08X}; // type:func allow_duplicated:True\n")
                for data in unit.data:
                    if data.name is None:
                        continue
                    f.write(f"{data.name:<32} = 0x{data.address:08X}; // size:{data.size} allow_duplicated:True\n")
                f.write("\n")
        
        f.write("// -- VU Symbols --\n\n")
        vudata_section = elf.get_section_by_name(".vudata")
        vutext_section = elf.get_section_by_name(".vutext")
        vudata_range = (vudata_section.header.sh_addr, vudata_section.header.sh_addr + vudata_section.header.sh_size)
        vutext_range = (vutext_section.header.sh_addr, vutext_section.header.sh_addr + vutext_section.header.sh_size)
        for label in stdump["labels"]:
            if (vudata_range[0] < label["address"] < vudata_range[1] or vutext_range[0] < label["address"] < vutext_range[1]) and not label["name"].startswith(("p", ".")):
                f.write(f"{label['name']:<32} = 0x{label['address']:08X}; // size:0 allow_duplicated:True\n")
        f.write("\n")

def write_splat_config(version: str, sections: list[Section]):
    subsegments = [
        SplatSegment(0x1000, "asm", "lib/crt0"),
        SplatSegment(0x10C8, "asm", "lib/tmp"),
        SplatSegment(0x1B9440, "asm", "lib/sce"),
        SplatSegment(0x1BFB70, "asm", "lib/gcc"),
        SplatSegment(0x1E4000, "data", "lib/tmp"),
        SplatSegment(0x1E4018, "data", "lib/gcc"),
        SplatSegment(0x274B00, "sdata", "lib/gcc"),
        SplatSegment(SECTION_ADDRS["sbss"], "sbss", "lib/sce", 0x375A00),
        SplatSegment(SECTION_ADDRS["sbss"], "sbss", "lib/gcc", 0x375A08),
        SplatSegment(SECTION_ADDRS["bss"], "bss", "lib/sce", 0x6D27C0),
        SplatSegment(SECTION_ADDRS["bss"], "bss", "lib/gcc", 0x6D7CA8),
    ]
    for section in sections:
        if "lib" in section.id:
            continue
        for unit in section.units:
            matching = os.path.exists(f"src/{section.path}/{unit.name}")
            if len(unit.functions) > 0:
                subsegments.append(SplatSegment(unit.functions[0].address - 0x100000 + 0x1000, unit.name.split(".")[1] if matching else "asm", f"{section.path}/{unit.name.split(".")[0]}"))
            for elf_section in ["data", "sdata", "sbss", "bss", "rodata", "lit4"]:
                data = unit.get_section_start(elf_section)
                if data is not None:
                    subsegments.append(SplatSegment(
                        (data.address - 0x100000 + 0x1000) if elf_section not in SECTION_ADDRS or elf_section == "rodata" else SECTION_ADDRS[elf_section],
                        f"{"." if matching else ""}{elf_section}",
                        f"{section.path}/{unit.name.split(".")[0]}",
                        data.address if elf_section in {"sbss", "bss"} else None
                    ))
    for elf_section in ["vutext", "vudata", "rodata", "gcc_except_table"]:
        subsegments.append(SplatSegment(SECTION_ADDRS[elf_section], SECTION_TYPE[elf_section], elf_section))
    subsegments.sort(key=lambda x: (x.start, x.vram))
    
    splat_config = {
        "name": "Klonoa 2: Lunatea's Veil (Demo Disc 2.3 Trial)",
        "sha1": "a3bb363a7b97f4f0bb4059b0d55dd38ca2a27082",
        "options": {
            "basename": "MAIN.ELF",
            "target_path": "MAIN.ELF",
            "base_path": "../..",
            "extensions_path": "tools/splat_ext",
            "symbol_addrs_path": f"config/{version}/symbol_addrs.txt",
            "undefined_funcs_auto_path": f"config/{version}/undefined_funcs_auto.txt",
            "undefined_syms_auto_path": f"config/{version}/undefined_syms_auto.txt",
            "compiler": "EEGCC",
            "platform": "ps2",
            "use_gp_rel_macro_nonmatching": False,
            "string_encoding": "SHIFT-JIS",
            "rodata_string_guesser_level": 2,
            "data_string_guesser_level": 2,
            "disasm_unknown": True,
            "named_regs_for_c_funcs": False,
            "gp_value": HexInt(0x3784F0),
            "subalign": None,
            "find_file_boundaries": True,
            "o_as_suffix": True,
            "disassemble_all": True,
            "section_order": [".text", ".data", ".rodata", ".lit4", ".sdata", ".sbss", ".bss"],
        },
        "segments": [
            SplatSegment(0, "databin", "elf_header"),
            {
                "name": "main",
                "type": "code",
                "start": HexInt(0x1000),
                "vram": HexInt(0x100000),
                "bss_size": HexInt(0x3622F4),
                "subsegments": subsegments
            },
            SplatSegment(0x276800, "databin", None),
            SplatSegment(0x276864, "databin", None),
            SplatSegment(0x27687C, "databin", None),
            SplatSegment(0x10B5CE6, None, None),
        ]
    }

    with open(f"config/{version}/splat.yml", "w") as f:
        yaml.dump(splat_config, f, sort_keys=False, Dumper=MyDumper)

def write_objdiff_config(sections: list[Section]):
    objdiff_units = []
    for section in sections:
        if "lib" in section.id:
            continue
        for unit in section.units:
            unit_name = unit.name.split(".")[0]
            objdiff_units.append({
                "name": f"{section.path}/{unit_name}",
                "target_path": f"build/asm/{section.path}/{unit_name}.o",
                "base_path": f"build/src/{section.path}/{unit_name}.o"
            })
    
    with open("objdiff.json", "w") as f:
        json.dump({
            "$schema": "https://raw.githubusercontent.com/encounter/objdiff/main/config.schema.json",
            "custom_make": "ninja",
            "watch_patterns": ["*.c", "*.cc", "*.cpp", "*.h", "*.asm", "*.o"],
            "units": objdiff_units
        }, f, indent=4)

def splat_stuff(version: str, make_full_disasm_for_code: bool = True) -> list[LinkerEntry]:
    yaml_file = Path(f"config/{version}/splat.yml")
    split.main([yaml_file], modes="all", verbose=False, make_full_disasm_for_code=make_full_disasm_for_code)
    return split.linker_writer.entries.copy()

def write_ninja_config(version: str, linker_entries: list[LinkerEntry], debug: bool = False):
    built_objects: set[Path] = set()

    def build(
        object_paths: Path | list[Path],
        src_paths: list[Path],
        task: str,
        variables: dict[str, str] = {},
        implicit: list[str] = [],
        implicit_outputs: list[str] = [],
        link: bool = True
    ):
        if not isinstance(object_paths, list):
            object_paths = [object_paths]

        object_strs = [str(obj) for obj in object_paths]

        for object_path in object_paths:
            if object_path.suffix == ".o" and link:
                built_objects.add(object_path)
            ninja.build(
                outputs=object_strs,
                rule=task,
                inputs=[str(s) for s in src_paths],
                implicit=implicit,
                variables=variables,
                implicit_outputs=implicit_outputs,
            )

    ninja = ninja_syntax.Writer(open(ROOT / "build.ninja", "w"), width=9999)

    ninja.rule(
        "as",
        description="as $in",
        command=f"cpp {COMMON_INCLUDES} $in -o  - | iconv -f=UTF-8 -t=SHIFT-JIS $in | {CROSS}-as -no-pad-sections -EL -march=5900 -mabi=eabi -Iinclude -o $out && build/tools/elf_patcher $out",
    )

    defines = [f"-DKL2_VER_{version.upper()}"]
    if debug:
        defines.append("-DKL2_DEBUG")
    defines_str = " ".join(defines)

    ninja.rule(
        "c",
        description="c $in",
        command=f"{COMPILE_CMD_C} {defines_str} $in -o $out && {CROSS}-strip $out -N dummy-symbol-name",
    )

    ninja.rule(
        "cpp",
        description="cpp $in",
        command=f"{COMPILE_CMD_CPP} {defines_str} $in -o $out && {CROSS}-strip $out -N dummy-symbol-name",
    )

    ninja.rule(
        "ld",
        description="link $out",
        command=f"{CROSS}-ld -EL -T config/{version}/undefined_syms.txt -T config/{version}/undefined_syms_auto.txt -T config/{version}/undefined_funcs_auto.txt -Map $mapfile -T $in -o $out",
    )

    ninja.rule(
        "sha1sum",
        description="sha1sum $in",
        command="sha1sum -c $in && touch $out",
    )

    ninja.rule(
        "elf",
        description="elf $out",
        command=f"{CROSS}-objcopy $in $out -O binary",
    )

    ninja.rule(
        "tool",
        description="tool $in",
        command="gcc -O2 $in -o $out && chmod +x $out"
    )

    ninja.build(
        "build/tools/elf_patcher",
        "tool",
        "tools/elf_patcher.c"
    )

    ninja.rule(
        "ld_asm",
        description="ld_asm $out",
        command=f"{CROSS}-ld -EL -r $in -o $out"
    )

    for entry in linker_entries:
        seg = entry.segment

        if seg.type[0] == ".":
            continue

        if entry.object_path is None:
            continue

        if isinstance(seg, splat.segtypes.common.asm.CommonSegAsm):
            build(entry.object_path, entry.src_paths, "as", implicit=["build/tools/elf_patcher"])
        elif isinstance(seg, splat.segtypes.common.cpp.CommonSegCpp):
            build(entry.object_path, entry.src_paths, "cpp")

            # Build ASM for objdiff
            # src_path = list(entry.src_paths[0].with_suffix(".s").parts)
            # src_path[0] = "asm"
            # object_path = list(entry.object_path.parts)
            # object_path[1] = "asm"
            # build(Path(*object_path), [Path(*src_path)], "as", implicit=["build/tools/elf_patcher"], link=False)
        elif isinstance(seg, splat.segtypes.common.c.CommonSegC):
            link_asm: list[Path] = []

            # Build code source
            build(entry.object_path, entry.src_paths, "c")

            # Build code ASM
            src_path = list(entry.src_paths[0].with_suffix(".s").parts)
            src_path[0] = "asm"
            object_path = list(entry.object_path.parts)
            object_path[1] = "asm"
            src = Path(*src_path)
            obj = Path(*object_path).with_suffix(".text.o")
            if src.exists():
                build(obj, [src], "as", implicit=["build/tools/elf_patcher"], link=False)
                link_asm.append(obj)

                # Fix ACC register
                with src.open("r") as f:
                    asm = f.read()
                with src.open("w") as f:
                    f.write(asm.replace(" ACC,", " $ACC,").replace(" Q,", " $Q,").replace(", Q", ", $Q"))

            # Build data ASMs
            src_path.insert(1, "data")
            object_path.insert(2, "data")
            for section, sibling in seg.siblings.items():
                src = Path(*src_path).with_suffix(section + ".s")
                obj = Path(*object_path).with_suffix(section + ".o")
                if src.exists():
                    build(obj, [src], "as", implicit=["build/tools/elf_patcher"], link=False)
                    link_asm.append(obj)
            
            # Link code + data ASMs
            del src_path[1]
            del object_path[2]
            if len(link_asm) > 0:
                build(Path(*object_path), link_asm, "ld_asm", link=False)
        elif isinstance(seg, splat.segtypes.common.data.CommonSegData):
            build(entry.object_path, entry.src_paths, "as", implicit=["build/tools/elf_patcher"])
        elif isinstance(seg, splat.segtypes.common.databin.CommonSegDatabin):
            build(entry.object_path, entry.src_paths, "as", implicit=["build/tools/elf_patcher"])
        elif isinstance(seg, splat.segtypes.common.rodatabin.CommonSegRodatabin):
            build(entry.object_path, entry.src_paths, "as", implicit=["build/tools/elf_patcher"])
        else:
            print(f"WARN: Unsupported build segment type {seg.type}")

    basename     = "MAIN.ELF" # TODO: change this
    ld_path      = f"{basename}.ld"
    elf_path     = f"build/{version}/{basename}"
    map_path     = f"build/{version}/{basename}.map"
    pre_elf_path = f"build/{version}/{basename}.elf"

    ninja.build(
        pre_elf_path,
        "ld",
        ld_path,
        implicit=[str(obj) for obj in built_objects],
        variables={"mapfile": map_path},
    )

    ninja.build(
        elf_path,
        "elf",
        pre_elf_path,
    )

    ninja.build(
        elf_path + ".ok",
        "sha1sum",
        f"config/{version}/checksum.sha1",
        implicit=[elf_path],
    )

def read_elf(elf_path: str) -> ELFFile:
    with open(elf_path, "rb") as f:
        elf = ELFFile(io.BytesIO(f.read()))
    return elf

def clean():
    for file in CLEAN_FILES:
        if os.path.exists(file):
            print(f"Deleting {file}...")
            os.remove(file)
    for dir in CLEAN_DIRS:
        print(f"Deleting {dir}/...")
        shutil.rmtree(dir, ignore_errors=True)
    print("Done!")

# this is cringe
class LinkerEntryWrapper:
    def __init__(self, entry: LinkerEntry):
        self.entry = entry

    def __hash__(self):
        return hash(self.entry.object_path)
    
    def __eq__(self, value: "LinkerEntryWrapper"):
        return hash(value.entry.object_path) == hash(self)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        prog="kl2_configure",
        description="Configures the development environment.",
        epilog="Wahoo!"
    )

    versions = os.listdir("config")
    versions.sort()
    parser.add_argument(
        "version",
        help="select the version to build",
        choices=versions,
        default=versions[0],
        nargs="*"
    )
    parser.add_argument(
        "-c", "--clean",
        action="store_true",
        help="clean the development environment and exit the program"
    )
    parser.add_argument(
        "-par", "--paruu",
        action="store_true",
        help="generate paruu config (temporary command)",
        default=True
    )
    parser.add_argument(
        "-spl", "--splat",
        action="store_true",
        help="generate splat and ninja config",
        default=True
    )
    parser.add_argument(
        "-sym", "--symbols",
        action="store_true",
        help="generate symbol_addrs.txt",
        default=True
    )
    parser.add_argument(
        "-p", "--progress",
        action="store_true",
        help="generate asm for matched files",
        default=False
    )

    args = parser.parse_args()

    if args.clean:
        clean()
        sys.exit(0)

    elf = read_elf("MAIN.ELF")
    with open("stdump.json") as f:
        stdump = json.load(f)
    
    if args.paruu:
        paruu = create_paruu_config(elf, stdump)
        write_paruu_config(args.version, paruu)
    
    if args.symbols:
        write_symbol_addrs(args.version, paruu, elf, stdump)

    if args.splat:
        write_objdiff_config(paruu)
        write_splat_config(args.version, paruu)
        splat_stuff(args.version, not args.progress)
        
        write_ninja_config(args.version, split.linker_writer.entries, debug=True)
        with open("compile_commands.json", "wb") as f:
            subprocess.run(["ninja", "-t", "compdb"], stdout=f)