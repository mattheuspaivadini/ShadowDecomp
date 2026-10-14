#!/usr/bin/env python3
"""Assemble + link the splat split and check the ELF/ROM hash (Phase 4).

Runs under WSL2 (Ubuntu) with `binutils-mips-linux-gnu` on PATH; the repo is
reachable at /mnt/c/... . The whole link layout comes from the linker script
splat generated (`build/SCUS_974.72.ld`), which references one object per
subsegment as `build/asm/<dir>/<name>.o`.

Usage (from WSL):
    python3 tools/build.py             # assemble + link + hash check
    python3 tools/build.py --jobs 8

Outputs `build/SCUS_974.72.elf` and `build/SCUS_974.72.bin` and compares the
flat binary's SHA-1 against the ROM hash pinned in the splat config.
"""

from __future__ import annotations

import argparse
import concurrent.futures
import hashlib
import os
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
LD_SCRIPT = ROOT / "build" / "SCUS_974.72.ld"
PATCHED_LD = ROOT / "build" / "SCUS_974.72.patched.ld"
ELF = ROOT / "build" / "SCUS_974.72.elf"
BIN = ROOT / "build" / "SCUS_974.72.bin"
MAP = ROOT / "build" / "SCUS_974.72.map"
EXPECTED_SHA1 = "6f853f644a4279db18c15ceb8ee1d2a8b87a7b39"  # build/SCUS_974.72.rom

AS = "mips-linux-gnu-as"
LD = "mips-linux-gnu-ld"
OBJCOPY = "mips-linux-gnu-objcopy"
AS_FLAGS = ["-EL", "-march=5900", "-mabi=eabi", "-no-pad-sections", "-Iinclude", "-I."]

OBJ_REF = re.compile(r"(build/[^\s():]+\.o)")


def object_refs() -> list[str]:
    text = LD_SCRIPT.read_text(encoding="utf-8", errors="replace")
    seen: list[str] = []
    for m in OBJ_REF.finditer(text):
        ref = m.group(1)
        if ref not in seen:
            seen.append(ref)
    return seen


def to_source(obj_rel: str) -> Path:
    # build/asm/cod/000010.o -> asm/cod/000010.s
    assert obj_rel.startswith("build/") and obj_rel.endswith(".o")
    return ROOT / (obj_rel[len("build/") : -len(".o")] + ".s")


def assemble(obj_rel: str) -> tuple[str, str]:
    src = to_source(obj_rel)
    if not src.exists():
        return (obj_rel, f"MISSING SOURCE {src}")
    cmd = [AS, *AS_FLAGS, "-o", str(ROOT / obj_rel), str(src)]
    (ROOT / obj_rel).parent.mkdir(parents=True, exist_ok=True)
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode != 0:
        return (obj_rel, (r.stderr or r.stdout).strip().splitlines()[0] if (r.stderr or r.stdout) else "as failed")
    # GAS emits 16-byte-aligned `.text`/`.data`, which makes the linker pad
    # between every function object (observed: +3428 bytes). The original image
    # is 4-byte-aligned, so force section alignment to 4 (this is what the SOTC
    # project's elf_patcher `--section-align .text:0x4` does).
    obj = ROOT / obj_rel
    tmp = str(obj) + ".al"
    sections = [".text", ".data", ".rodata", ".lit4", ".sdata", ".sbss", ".bss"]
    align_args: list[str] = []
    for s in sections:
        align_args += ["--set-section-alignment", f"{s}=4"]
    al = subprocess.run(
        [OBJCOPY, *align_args, str(obj), tmp],
        capture_output=True, text=True,
    )
    if al.returncode != 0:
        return (obj_rel, "objcopy align failed: " + (al.stderr or al.stdout).strip().splitlines()[0])
    os.replace(tmp, obj)
    return (obj_rel, "")


def sha1(path: Path) -> str:
    h = hashlib.sha1()
    with path.open("rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--jobs", type=int, default=os.cpu_count() or 4)
    args = ap.parse_args()

    refs = object_refs()
    missing = [r for r in refs if not to_source(r).exists()]
    print(f"{len(refs)} objects referenced by the linker script")
    if missing:
        print(f"  {len(missing)} with NO source:")
        for r in missing[:20]:
            print(f"    {r}")

    failures: list[tuple[str, str]] = []
    with concurrent.futures.ThreadPoolExecutor(max_workers=args.jobs) as ex:
        for obj_rel, err in ex.map(assemble, refs):
            if err:
                failures.append((obj_rel, err))
    if failures:
        print(f"\n{len(failures)} assembly failures (showing up to 25):")
        for obj_rel, err in failures[:25]:
            print(f"  {obj_rel}: {err}")
        return 1
    print("assemble: OK")

    # splat emits `. = ALIGN(., 16);` at the end of every output section, which
    # injects padding the original image does not have (observed +16 bytes and
    # shifted sections). Strip those lines for the link.
    ld_text = LD_SCRIPT.read_text(encoding="utf-8", errors="replace")
    kept = [ln for ln in ld_text.splitlines() if ". = ALIGN(., 16);" not in ln]
    PATCHED_LD.write_text("\n".join(kept) + "\n", encoding="utf-8", newline="\n")

    link_cmd = [
        LD, "-EL",
        "-T", "undefined_syms_auto.txt",
        "-T", "undefined_funcs_auto.txt",
        "-Map", str(MAP),
        "-T", str(PATCHED_LD),
        "-o", str(ELF),
    ]
    r = subprocess.run(link_cmd, cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        print("link FAILED:")
        print((r.stderr or r.stdout)[:4000])
        return 1
    print("link: OK")

    subprocess.run([OBJCOPY, str(ELF), str(BIN), "-O", "binary"], check=True)
    got = sha1(BIN)
    size = BIN.stat().st_size
    print(f"bin: {size} bytes  sha1 {got}")
    print(f"expected ROM sha1   {EXPECTED_SHA1}")
    ok = got == EXPECTED_SHA1
    print("HASH MATCH" if ok else "HASH MISMATCH")
    return 0 if ok else 2


if __name__ == "__main__":
    sys.exit(main())
