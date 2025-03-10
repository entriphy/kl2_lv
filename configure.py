from dataclasses import dataclass
import json
import os
from pathlib import Path
import shutil
import yaml

import ninja_syntax
import splat
import splat.scripts.split as split
from splat.segtypes.linker_entry import LinkerEntry

ROOT = Path(__file__).parent.resolve()
TOOLS_DIR = ROOT / "tools"

VERSION = "trial"
BASENAME = "MAIN.ELF"

CROSS        = "mips-linux-gnu-"
LD_PATH      = f"{BASENAME}.ld"
ELF_PATH     = f"build/{VERSION}/{BASENAME}"
MAP_PATH     = f"build/{VERSION}/{BASENAME}.map"
PRE_ELF_PATH = f"build/{VERSION}/{BASENAME}.elf"

COMPILER_ID        = "ee-gcc"
COMPILER_VER       = "2.9-991111-01"
COMPILER_DIR       = f"{TOOLS_DIR}/cc/{COMPILER_ID}{COMPILER_VER}"
COMMON_INCLUDES    = f"-Iinclude -Isrc -isystem lib/ee -isystem lib -isystem {COMPILER_DIR}/ee/include -isystem {COMPILER_DIR}/lib/gcc-lib/ee/2.9-ee-991111-01/include"
COMPILER_FLAGS_C   = "-O1 -gstabs" # TODO: does this use -G8?
COMPILER_FLAGS_CPP = "-O2 -gstabs -x c++ -fno-exceptions"
COMPILER_DEFINES   = f"-DKL2_VER_{VERSION.upper()}"
COMPILE_CMD_C      = f"{COMPILER_DIR}/bin/ee-gcc -c {COMMON_INCLUDES} {COMPILER_FLAGS_C} {COMPILER_DEFINES}"
COMPILE_CMD_CPP    = f"{COMPILER_DIR}/bin/ee-gcc -c {COMMON_INCLUDES} {COMPILER_FLAGS_CPP} {COMPILER_DEFINES}"

CLEAN_FILES = [".splache", ".ninja_log", "build.ninja", "MAIN.ELF.ld", "permuter_settings.toml", "compile_commands.json"]
CLEAN_DIRS  = ["asm", "assets", "build"]

class HexInt(int): ...
def representer(dumper, data): return yaml.ScalarNode('tag:yaml.org,2002:int', f"0x{data:06X}")
yaml.add_representer(HexInt, representer)

class MyDumper(yaml.Dumper):
    def increase_indent(self, flow=False, indentless=False):
        return super(MyDumper, self).increase_indent(flow, False)

SECTION_ADDRS = {
    "vutext": 0x1E1900,
    "vudata": 0x253000,
    # "rodata": 0x260F00,
    "rodata": 0x361410 - 0x100000 + 0x1000,
    "gcc_except_table": 0x271400,
    "lit4": 0x271500,
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
        if self.functions: d["functions"] = self.functions
        if self.data: d["data"] = self.data
        return d
    
    def get_section_start(self, section: str) -> Data | None:
        arr = [data for data in self.data if data.section == section]
        return min(arr, key=lambda x: x.address) if arr else None


@dataclass
class Category:
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
                (yaml.ScalarNode("tag:yaml.org,2002:str", f"start"), yaml.ScalarNode("tag:yaml.org,2002:int", f"0x{data.start:06X}")),
                (yaml.ScalarNode("tag:yaml.org,2002:str", f"type"), yaml.ScalarNode("tag:yaml.org,2002:str", data.type)),
                (yaml.ScalarNode("tag:yaml.org,2002:str", f"vram"), yaml.ScalarNode("tag:yaml.org,2002:int", f"0x{data.vram:06X}")),
                (yaml.ScalarNode("tag:yaml.org,2002:str", f"name"), yaml.ScalarNode("tag:yaml.org,2002:str", data.name)),
            ],
            flow_style=True
        )

yaml.add_representer(Function, Function.representer)
yaml.add_representer(Data, Data.representer)
yaml.add_representer(SplatSegment, SplatSegment.representer)

def read_paruu(stdump_json: str) -> list[Category]:
    with open(stdump_json) as f:
        stdump = json.load(f)
    
    categories: dict[str, Category] = {}
    duplicates: dict[str, list[Function | Data]] = {}
    lib_category = Category("lib", "lib", [])
    lib_unit = Unit("sdk", [], [])
    lib_category.units.append(lib_unit)
    for source_file in stdump["source_files"]:
        source_file_split: str = source_file["name"].split("/home/hoshino/trial/src/")
        if len(source_file_split) == 1:
            category = lib_category
            unit = lib_unit
        else:
            source_file_dir = "/".join(source_file_split[1].split("/")[:-1])
            source_file_unit = source_file_split[1].split("/")[-1]
            source_file_lang = source_file_unit.split(".")[-1]
            category_id = f"{source_file_dir}:{source_file_lang}"
            if category_id not in categories:
                category = Category(category_id, category_id.split(":")[0], [])
                categories[category_id] = category
            else:
                category = categories[category_id]
            unit = Unit(source_file_unit, [], [])
            category.units.append(unit)

        for global_variable in map(lambda x: stdump["global_variables"][x], source_file.get("global_variables", [])):
            data = Data(global_variable["name"], global_variable["address"], global_variable["storage"]["location"], global_variable.get("size", 0))
            unit.data.append(data)

            if data.name not in duplicates:
                duplicates[data.name] = []
            duplicates[data.name].append(data)

        for function in map(lambda x: stdump["functions"][x], source_file.get("functions", [])):
            func = Function(function["name"], function["address"])
            unit.functions.append(func)
            if func.name not in duplicates:
                duplicates[func.name] = []
            duplicates[func.name].append(func)

            for local_variable in map(lambda x: stdump["local_variables"][x], function.get("local_variables", [])):
                if local_variable["storage"]["type"] not in {"register", "stack"}:
                    data = Data(local_variable["name"], local_variable["address"], local_variable["storage"]["location"], local_variable.get("size", 0))
                    unit.data.append(data)

                    if data.name not in duplicates:
                        duplicates[data.name] = []
                    duplicates[data.name].append(data)
        
        unit.functions.sort(key=lambda x: x.address)
        unit.data.sort(key=lambda x: x.address)
    
    categories["lib"] = lib_category

    sdata_fix = {
        "abe:c": {
            "ab_menu.c": 0x373B08,
            "firetest.c": 0x373B40,
        },
        "harada:c": {
            "hr_main.c": 0x373B60,
            "hr_mapv.c": 0x373C90
        },
        "nakano:c": {
            "map01.c": 0x374BB8
        }
    }

    rodata_fix = {
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
        }
    }

    for category, units in sdata_fix.items():
        for unit, address in units.items():
            next(u for u in categories[category].units if u.name == unit).data.append(Data(None, address, "sdata", 0))
    
    for category, units in rodata_fix.items():
        for unit, address in units.items():
            next(u for u in categories[category].units if u.name == unit).data.append(Data(None, address, "rodata", 0))

    for name, stuff in duplicates.items():
        if len(stuff) > 1:
            for i, thing in enumerate(stuff):
                thing.name = f"{thing.name}.{i}"
    
    return list(categories.values())

def write_paruu_config(version: str, categories: list[Category]):
    with open(f"config/{version}/paruu.yml", "w") as f:
        paruu_config = {
            "id": "lv",
            "version": "trial",
            "name": "Klonoa 2: Lunatea's Veil (Demo Disc 2.3 Trial)",
            "platform": "ps2",
            "repository": "https://github.com/entriphy/kl2_lv_decomp",
            "src": "src",
            "sections": [category.dump() for category in categories]
        }
        yaml.dump(paruu_config, f, sort_keys=False, Dumper=MyDumper, default_flow_style=False)

def write_symbol_addrs(version: str, categories: list[Category]):
    with open(f"config/{version}/symbol_addrs.txt", "w") as f:
        for category in categories:
            f.write(f"// -- {category.id} --\n\n")
            for unit in category.units:
                f.write(f"// {category.path}/{unit.name}\n")
                for function in unit.functions:
                    f.write(f"{function.name:<32} = 0x{function.address:08X}; // type:func allow_duplicated:True\n")
                for data in unit.data:
                    if data.name is None: continue
                    f.write(f"{data.name:<32} = 0x{data.address:08X}; // size:{data.size} allow_duplicated:True\n")
                f.write("\n")

def write_splat_config(version: str, categories: list[Category], asm_only: bool = False):
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
    for category in categories:
        if "lib" in category.id:
            continue
        for unit in category.units:
            matching = os.path.exists(f"src/{category.path}/{unit.name}")
            if len(unit.functions) > 0:
                subsegments.append(SplatSegment(unit.functions[0].address - 0x100000 + 0x1000, "c" if matching and not asm_only else "asm", f"{category.path}/{unit.name.split(".")[0]}"))
            for section in ["data", "sdata", "sbss", "bss", "rodata", "lit4"]:
                if (data := unit.get_section_start(section)) is not None:
                    subsegments.append(SplatSegment(
                        (data.address - 0x100000 + 0x1000) if section not in SECTION_ADDRS or section == "rodata" else SECTION_ADDRS[section],
                        f"{"." if matching and not asm_only else ""}{section}",
                        f"{category.path}/{unit.name.split(".")[0]}",
                        data.address if section in {"sbss", "bss"} else None
                    ))
    for section in ["vutext", "vudata", "rodata", "gcc_except_table", "lit4"]:
        subsegments.append(SplatSegment(SECTION_ADDRS[section], SECTION_TYPE[section], section))
    subsegments.sort(key=lambda x: (x.start, x.vram))
    
    splat_config = {
        "name": "Klonoa 2: Lunatea's Veil (Demo Disc 2.3 Trial)",
        "sha1": "a3bb363a7b97f4f0bb4059b0d55dd38ca2a27082",
        "options": {
            "basename": "MAIN.ELF",
            "target_path": "MAIN.ELF",
            "base_path": "../..",
            "symbol_addrs_path": "config/trial/symbol_addrs.txt",
            "undefined_funcs_auto_path": "config/trial/undefined_funcs_auto.txt",
            "undefined_syms_auto_path": "config/trial/undefined_syms_auto.txt",
            "compiler": "EEGCC",
            "platform": "ps2",
            "use_gp_rel_macro_nonmatching": False,
            "string_encoding": "EUC-JP",
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

def write_objdiff_config(categories: list[Category]):
    objdiff_units = []
    for category in categories:
        if "lib" in category.id:
            continue
        for unit in category.units:
            unit_name = unit.name.split(".")[0]
            objdiff_units.append({
                "name": f"{category.path}/{unit_name}",
                "target_path": f"build/objdiff/{category.path}/{unit_name}.o",
                "base_path": f"build/src/{category.path}/{unit_name}.o"
            })
    
    with open("objdiff.json", "w") as f:
        json.dump({
            "$schema": "https://raw.githubusercontent.com/encounter/objdiff/main/config.schema.json",
            "custom_make": "ninja",
            "watch_patterns": ["*.c", "*.cc", "*.h", "*.asm"],
            "units": objdiff_units
        }, f, indent=4)

def splat_stuff(version: str) -> list[LinkerEntry]:
    yaml_file = f"config/{version}/splat.yml"
    split.main([yaml_file], modes="all", verbose=False)
    return split.linker_writer.entries.copy()

def write_ninja_config(version: str, linker_entries: list[LinkerEntry], objdiff_entries: list[LinkerEntry]):
    built_objects: set[Path] = set()

    def build(
        object_paths: Path | list[Path],
        src_paths: list[Path],
        task: str,
        variables: dict[str, str] = {},
        implicit_outputs: list[str] = [],
        asm_only: bool = False
    ):
        if not isinstance(object_paths, list):
            object_paths = [object_paths]

        object_strs = [str(obj) for obj in object_paths]

        for object_path in object_paths:
            if object_path.suffix == ".o" and not asm_only:
                built_objects.add(object_path)
            ninja.build(
                outputs=object_strs,
                rule=task,
                inputs=[str(s) for s in src_paths],
                variables=variables,
                implicit_outputs=implicit_outputs,
            )

    ninja = ninja_syntax.Writer(open(ROOT / "build.ninja", "w"), width=9999)

    ninja.rule(
        "as",
        description="as $in",
        command=f"cpp {COMMON_INCLUDES} $in -o  - | iconv -f=UTF-8 -t=EUC-JP $in | {CROSS}as -no-pad-sections -EL -march=5900 -mabi=eabi -Iinclude -o $out && python3 tools/elf_patcher.py $out gas",
    )

    ninja.rule(
        "c",
        description="c $in",
        command=f"{COMPILE_CMD_C} $in -o $out && {CROSS}strip $out -N dummy-symbol-name",
    )

    ninja.rule(
        "cpp",
        description="cpp $in",
        command=f"{COMPILE_CMD_CPP} $in -o $out && {CROSS}strip $out -N dummy-symbol-name",
    )

    ninja.rule(
        "ld",
        description="link $out",
        command=f"{CROSS}ld -EL -T config/{version}/undefined_syms.txt -T config/{version}/undefined_syms_auto.txt -T config/{version}/undefined_funcs_auto.txt -Map $mapfile -T $in -o $out",
    )

    ninja.rule(
        "sha1sum",
        description="sha1sum $in",
        command="sha1sum -c $in && touch $out",
    )

    ninja.rule(
        "elf",
        description="elf $out",
        command=f"{CROSS}objcopy $in $out -O binary",
    )

    ninja.rule(
        "objdiff",
        description="objdiff $out",
        command=f"{CROSS}ld -EL -r $in -o $out"
    )

    for entry in linker_entries:
        seg = entry.segment

        if seg.type[0] == ".":
            continue

        if entry.object_path is None:
            continue

        if isinstance(seg, splat.segtypes.common.asm.CommonSegAsm):
            build(entry.object_path, entry.src_paths, "as")
        elif isinstance(seg, splat.segtypes.common.c.CommonSegC):
            build(entry.object_path, entry.src_paths, "c")
        elif isinstance(seg, splat.segtypes.common.cpp.CommonSegCpp):
            build(entry.object_path, entry.src_paths, "cpp")
        elif isinstance(seg, splat.segtypes.common.data.CommonSegData):
            build(entry.object_path, entry.src_paths, "as")
        elif isinstance(seg, splat.segtypes.common.databin.CommonSegDatabin):
            build(entry.object_path, entry.src_paths, "as")
        elif isinstance(seg, splat.segtypes.common.rodatabin.CommonSegRodatabin):
            build(entry.object_path, entry.src_paths, "as")
        else:
            print(f"WARN: Unsupported build segment type {seg.type}")

    ninja.build(
        PRE_ELF_PATH,
        "ld",
        LD_PATH,
        implicit=[str(obj) for obj in built_objects],
        variables={"mapfile": MAP_PATH},
    )

    ninja.build(
        ELF_PATH,
        "elf",
        PRE_ELF_PATH,
    )

    ninja.build(
        ELF_PATH + ".ok",
        "sha1sum",
        f"config/{VERSION}/checksum.sha1",
        implicit=[ELF_PATH],
    )

    objdiff_ld: dict[str, list[LinkerEntry]] = {}
    for entry in objdiff_entries:
        if entry.segment.name not in objdiff_ld:
            objdiff_ld[entry.segment.name] = []
        objdiff_ld[entry.segment.name].append(entry)
    for unit, entries in objdiff_ld.items():
        inputs = []
        for entry in entries:
            build(entry.object_path, entry.src_paths, "as", asm_only=True)
            inputs.append(str(entry.object_path))
        ninja.build(
            f"build/objdiff/{unit}.o",
            "objdiff",
            inputs
        )


def clean():
    for file in CLEAN_FILES:
        if os.path.exists(file):
            os.remove(file)
    for dir in CLEAN_DIRS:
        shutil.rmtree(dir, ignore_errors=True)

# this is cringe
class LinkerEntryWrapper:
    def __init__(self, entry: LinkerEntry):
        self.entry = entry

    def __hash__(self):
        return hash(self.entry.object_path)
    
    def __eq__(self, value: "LinkerEntryWrapper"):
        return hash(value.entry.object_path) == hash(self)

if __name__ == "__main__":
    clean()
    paruu = read_paruu("stdump.json")
    write_paruu_config("trial", paruu)
    write_symbol_addrs("trial", paruu)

    write_splat_config("trial", paruu, asm_only=True) # this
    yeet1 = splat_stuff("trial") # is
    write_splat_config("trial", paruu, asm_only=False) # dumb
    yeet2 = splat_stuff("trial") # but i have to do this to force splat to emit the assembly per-segment if the source file exists D:

    thing = set(LinkerEntryWrapper(entry) for entry in yeet1) - set(LinkerEntryWrapper(entry) for entry in yeet2)
    write_ninja_config("trial", split.linker_writer.entries, [entry.entry for entry in thing])
    write_objdiff_config(paruu)