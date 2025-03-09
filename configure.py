#! /usr/bin/env python3

import argparse
import os
import shutil
import sys
from pathlib import Path
from typing import Dict, List, Set, Union

import ninja_syntax
import splat
import splat.scripts.split as split
from splat.segtypes.linker_entry import LinkerEntry

ROOT = Path(__file__).parent.resolve()
TOOLS_DIR = ROOT / "tools"

VERSION = "trial"
BASENAME = "MAIN.ELF"
YAML_FILE = f"config/{VERSION}/splat.yaml"

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
COMPILE_CMD_C      = f"{COMPILER_DIR}/bin/ee-gcc -c {COMMON_INCLUDES} {COMPILER_FLAGS_C}"
COMPILE_CMD_CPP    = f"{COMPILER_DIR}/bin/ee-gcc -c {COMMON_INCLUDES} {COMPILER_FLAGS_CPP}"


def clean():
    if os.path.exists(".splache"):
        os.remove(".splache")
    if os.path.exists(".ninja_log"):
        os.remove(".ninja_log")
    if os.path.exists("build.ninja"):
        os.remove("build.ninja")
    if os.path.exists("MAIN.ELF.ld"):
        os.remove("MAIN.ELF.ld")
    shutil.rmtree("asm", ignore_errors=True)
    shutil.rmtree("assets", ignore_errors=True)
    shutil.rmtree("build", ignore_errors=True)


def write_permuter_settings():
    with open("permuter_settings.toml", "w") as f:
        f.write(
            f"""compiler_command = "{COMPILER_DIR}/bin/ee-gcc -c -Iinclude -Iinclude/sdk/ee -Iinclude/gcc -Iinclude/gcc/gcc-lib -O1 -gstabs -D__GNUC__"
assembler_command = "mips-linux-gnu-as -march=r5900 -mabi=eabi -Iinclude"
compiler_type = "gcc"

[preserve_macros]

[decompme.compilers]
"tools/build/cc/gcc/gcc" = "ee-gcc2.9-991111-01"
"""
        )


def build_stuff(linker_entries: List[LinkerEntry]):
    built_objects: Set[Path] = set()

    def build(
        object_paths: Union[Path, List[Path]],
        src_paths: List[Path],
        task: str,
        variables: Dict[str, str] = {},
        implicit_outputs: List[str] = [],
    ):
        if not isinstance(object_paths, list):
            object_paths = [object_paths]

        object_strs = [str(obj) for obj in object_paths]

        for object_path in object_paths:
            if object_path.suffix == ".o":
                built_objects.add(object_path)
            ninja.build(
                outputs=object_strs,
                rule=task,
                inputs=[str(s) for s in src_paths],
                variables=variables,
                implicit_outputs=implicit_outputs,
            )

    ninja = ninja_syntax.Writer(open(str(ROOT / "build.ninja"), "w"), width=9999)

    # Rules
    cross = "mips-linux-gnu-"
    config = f"config/{VERSION}"
    ld_args = f"-EL -T {config}/undefined_syms.txt -T {config}/undefined_syms_auto.txt -T {config}/undefined_funcs_auto.txt -Map $mapfile -T $in -o $out"

    ninja.rule(
        "as",
        description="as $in",
        command=f"cpp {COMMON_INCLUDES} $in -o  - | iconv -f=UTF-8 -t=EUC-JP $in | {cross}as -no-pad-sections -EL -march=5900 -mabi=eabi -Iinclude -o $out && python3 tools/elf_patcher.py $out gas",
    )

    ninja.rule(
        "c",
        description="c $in",
        command=f"{COMPILE_CMD_C} $in -o $out && {cross}strip $out -N dummy-symbol-name",
    )

    ninja.rule(
        "cpp",
        description="cpp $in",
        command=f"{COMPILE_CMD_CPP} $in -o $out && {cross}strip $out -N dummy-symbol-name",
    )

    ninja.rule(
        "ld",
        description="link $out",
        command=f"{cross}ld {ld_args}",
    )

    ninja.rule(
        "sha1sum",
        description="sha1sum $in",
        command="sha1sum -c $in && touch $out",
    )

    ninja.rule(
        "elf",
        description="elf $out",
        command=f"{cross}objcopy $in $out -O binary",
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
            print(f"ERROR: Unsupported build segment type {seg.type}")
            sys.exit(1)

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


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Configure the project")
    parser.add_argument(
        "-v",
        "--version",
        help="Game version to configure for",
        choices=["trial"],
    )
    parser.add_argument(
        "-c",
        "--clean",
        help="Clean extraction and build artifacts",
        action="store_true",
    )
    args = parser.parse_args()

    if args.version:
        VERSION = args.version
    else:
        VERSION = "trial"

    BASENAME = {
        "trial": "MAIN.ELF",
    }[VERSION]

    LD_PATH = f"{BASENAME}.ld"
    ELF_PATH = f"build/{VERSION}/{BASENAME}"
    MAP_PATH = f"build/{VERSION}/{BASENAME}.map"
    PRE_ELF_PATH = f"build/{VERSION}/{BASENAME}.elf"

    if args.clean:
        clean()

    EXTENDEDNAME = {
        "trial": "Demo Disc 2.3 Trial",
    }[VERSION]

    print(
        f"Klonoa 2: Lunatea's Veil ~ Generating build configuration for {EXTENDEDNAME} edition ({BASENAME})"
    )

    YAML_FILE = f"config/{VERSION}/splat.yml"

    split.main([YAML_FILE], modes="all", verbose=False)

    linker_entries = split.linker_writer.entries

    build_stuff(linker_entries)

    write_permuter_settings()