#!/usr/bin/env python3
"""Assemble/compile + link the splat split and check the flat-image hash.

Runs under WSL2 (Ubuntu) with `binutils-mips-linux-gnu` on PATH and with
`tools/cc/eegcc.sh` available (see docs/toolchain.md). The link layout comes
from the linker script splat generated (`build/SCUS_974.72.ld`), which
references one object per subsegment as `build/asm/<dir>/<name>.o`.

A function can be either

* its original splat `.s` (default), or
* matching C listed in `config/c_sources.txt`,

and the flat load image must stay byte-identical either way:

Usage (from WSL):
    python3 tools/build.py                 # build + hash check
    python3 tools/build.py --jobs 8
    python3 tools/build.py --check         # same, but fail loudly on mismatch
    python3 tools/build.py --targets       # also emit objdiff target objects
    python3 tools/build.py --only 002FE0   # rebuild just that object

Outputs `build/SCUS_974.72.elf` / `.bin` and compares the flat binary's SHA-1
against the hash pinned in `config/compiler_flags.mk`.
"""
from __future__ import annotations

import argparse
import concurrent.futures
import hashlib
import os
import re
import struct
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import eegcc  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
LD_SCRIPT = ROOT / "build" / "SCUS_974.72.ld"
PATCHED_LD = ROOT / "build" / "SCUS_974.72.patched.ld"
ELF = ROOT / "build" / "SCUS_974.72.elf"
BIN = ROOT / "build" / "SCUS_974.72.bin"
MAP = ROOT / "build" / "SCUS_974.72.map"
TARGET_DIR = ROOT / "build" / "target"
C_SOURCES = ROOT / "config" / "c_sources.txt"

EXPECTED_SHA1 = eegcc.flag("ROM_SHA1", "6f853f644a4279db18c15ceb8ee1d2a8b87a7b39")
EXPECTED_SIZE = int(eegcc.flag("ROM_SIZE", "237952"), 0)
ROM_BASE = 0x00100000

AS = eegcc.flag("EE_AS", "mips-linux-gnu-as")
LD = eegcc.flag("EE_LD", "mips-linux-gnu-ld")
OBJCOPY = eegcc.flag("EE_OBJCOPY", "mips-linux-gnu-objcopy")
AS_FLAGS = eegcc.flag(
    "EE_ASFLAGS", "-EL -march=5900 -mabi=eabi -no-pad-sections -Iinclude -I.").split()
ALIGN_SECTIONS = [".text", ".data", ".rodata", ".lit4", ".sdata", ".sbss", ".bss"]

OBJ_REF = re.compile(r"(build/[^\s():]+\.o)")
SIZE_RE = re.compile(r"^nonmatching\s+\S+,\s*0x([0-9A-Fa-f]+)\s*$", re.M)
# Sections that carry game data: a C object contributing any of these would be
# placed at this function's position by the linker script and shift the original
# data layout, so it is refused (see compile_object).
DATA_SECTIONS = {".data", ".rodata", ".data_nop", ".sdata", ".sbss", ".bss",
                 ".lit4", ".text_nop", ".ctors", ".dtors", ".eh_frame"}


def _load_c_manifest() -> dict[str, tuple[str, list[str], str | None]]:
    """object stem -> (C source, extra flags, compiler) from config/c_sources.txt.

    Entry format:  <stem> = <C source> [<extra flags> ...] [cc=<token>]

    The extra flags exist because the original binary mixes debug levels: e.g.
    func_00114C30 only matches with `-g0` while func_00104E78 only matches with
    `-g2` (the `-g` level changes the EE-GCC delay-slot scheduling).

    `cc=<token>` pins the EE-GCC distribution for this translation unit (see
    tools/eegcc.py:resolve_compiler). Evidence: the original is a mixture of the
    2.9-991111 and 2.96 EE-GCC generations (docs/compiler.md section 4.3).
    """
    out: dict[str, tuple[str, list[str], str | None]] = {}
    if not C_SOURCES.exists():
        return out
    for line in C_SOURCES.read_text(encoding="utf-8").splitlines():
        line = line.split("#", 1)[0].strip()
        if not line or "=" not in line:
            continue
        stem, rest = (p.strip() for p in line.split("=", 1))
        parts = rest.split()
        if not parts:
            continue
        flags: list[str] = []
        compiler: str | None = None
        for tok in parts[1:]:
            if tok.startswith("cc="):
                compiler = tok[3:]
            else:
                flags.append(tok)
        out[stem] = (parts[0], flags, compiler)
    return out


_MANIFEST = _load_c_manifest()


def load_c_sources() -> dict[str, str]:
    return {k: v[0] for k, v in _MANIFEST.items()}


def load_c_flags(stem: str) -> list[str]:
    return _MANIFEST.get(stem, ("", [], None))[1]


def load_c_compiler(stem: str) -> str | None:
    return _MANIFEST.get(stem, ("", [], None))[2]


def object_refs() -> list[str]:
    text = LD_SCRIPT.read_text(encoding="utf-8", errors="replace")
    seen: list[str] = []
    for m in OBJ_REF.finditer(text):
        if m.group(1) not in seen:
            seen.append(m.group(1))
    return seen


def to_source(obj_rel: str) -> Path:
    # build/asm/cod/000010.o -> asm/cod/000010.s
    assert obj_rel.startswith("build/") and obj_rel.endswith(".o")
    return ROOT / (obj_rel[len("build/"):-len(".o")] + ".s")


def stem_of(obj_rel: str) -> str:
    return Path(obj_rel).stem


def original_size(src: Path) -> int | None:
    """The function-body size splat recorded in the .s (`nonmatching NAME, 0xN`).

    NOTE: this excludes trailing `nop` alignment padding that splat emits after
    `endlabel`, so it is *not* the object's `.text` size - use
    `asm_text_size()` for that.
    """
    if not src.exists():
        return None
    m = SIZE_RE.search(src.read_text(encoding="utf-8", errors="replace"))
    return int(m.group(1), 16) if m else None


def asm_text_size(obj_rel: str) -> tuple[int, str]:
    """Exact `.text` size of the object built from the original .s.

    This is the ground truth for padding a C replacement: it includes the
    trailing alignment `nop`s that the original `endlabel` block is followed by.
    """
    src = to_source(obj_rel)
    if not src.exists():
        return 0, f"missing source {src}"
    tmp = ROOT / "build" / "tmp" / (stem_of(obj_rel) + ".orig.o")
    tmp.parent.mkdir(parents=True, exist_ok=True)
    r = subprocess.run([AS, *AS_FLAGS, "-o", str(tmp), str(src)],
                       capture_output=True, text=True)
    if r.returncode != 0:
        msg = (r.stderr or r.stdout).strip().splitlines()
        return 0, "as failed: " + (msg[0] if msg else "?")
    return eegcc.section_sizes(tmp).get(".text", 0), ""


def align_args() -> list[str]:
    args: list[str] = []
    for s in ALIGN_SECTIONS:
        args += ["--set-section-alignment", f"{s}=4"]
    return args


def assemble(obj_rel: str) -> tuple[str, str]:
    src = to_source(obj_rel)
    if not src.exists():
        return (obj_rel, f"MISSING SOURCE {src}")
    obj = ROOT / obj_rel
    obj.parent.mkdir(parents=True, exist_ok=True)
    cmd = [AS, *AS_FLAGS, "-o", str(obj), str(src)]
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode != 0:
        msg = (r.stderr or r.stdout).strip().splitlines()
        return (obj_rel, msg[0] if msg else "as failed")
    # GAS marks .text/.data 16-byte aligned, which makes the linker pad between
    # every function object (observed: +3428 bytes). The original image is
    # 4-byte aligned, so force section alignment to 4.
    tmp = str(obj) + ".al"
    al = subprocess.run([OBJCOPY, *align_args(), str(obj), tmp],
                        capture_output=True, text=True)
    if al.returncode != 0:
        msg = (al.stderr or al.stdout).strip().splitlines()
        return (obj_rel, "objcopy align failed: " + (msg[0] if msg else "?"))
    os.replace(tmp, obj)
    return (obj_rel, "")


def compile_object(obj_rel: str, src_rel: str) -> tuple[str, str]:
    """Compile C and align its sections; the linker pins the exact span."""
    obj = ROOT / obj_rel
    want, werr = asm_text_size(obj_rel)
    if werr:
        return (obj_rel, f"cannot size original object: {werr}")
    if want == 0:
        return (obj_rel, "original object has an empty .text")

    err = eegcc.compile_c(src_rel, obj, load_c_flags(stem_of(obj_rel)),
                          compiler=load_c_compiler(stem_of(obj_rel)))
    if err:
        return (obj_rel, f"ee-gcc: {err}")

    alloc = {k: v for k, v in eegcc.section_sizes(obj).items()
             if k in DATA_SECTIONS and v}
    if alloc:
        # A C object that contributes .rodata/.data/.sdata/.bss would be placed
        # by the linker script at the position of *this* function, shifting the
        # original data layout. Refuse loudly instead of silently breaking the
        # hash. (Support for that needs a splat `c` subsegment.)
        return (obj_rel, f"unsupported allocatable sections in C object: {alloc}")

    got = eegcc.section_sizes(obj).get(".text", 0)
    if got > want:
        return (obj_rel, f"compiled .text is {got} bytes > original {want}")

    # NOTE: never use `objcopy --update-section` here - it drops the object's
    # `.rel.text` entries, so %hi/%lo stay 0 and the link silently produces
    # wrong instructions. Section alignment only rewrites section headers.
    tmp = str(obj) + ".al"
    r = subprocess.run([OBJCOPY, *align_args(), str(obj), tmp],
                       capture_output=True, text=True)
    if r.returncode != 0:
        msg = (r.stderr or r.stdout).strip().splitlines()
        return (obj_rel, "objcopy align failed: " + (msg[0] if msg else "?"))
    os.replace(tmp, obj)
    return (obj_rel, "")


def assemble_target(obj_rel: str) -> tuple[str, str]:
    """Build the objdiff *target* object (the original .s) for a function."""
    src = to_source(obj_rel)
    if not src.exists():
        return (obj_rel, "missing source")
    out = TARGET_DIR / obj_rel[len("build/"):]
    out.parent.mkdir(parents=True, exist_ok=True)
    r = subprocess.run([AS, *AS_FLAGS, "-o", str(out), str(src)],
                       capture_output=True, text=True)
    if r.returncode != 0:
        msg = (r.stderr or r.stdout).strip().splitlines()
        return (obj_rel, msg[0] if msg else "as failed")
    return (obj_rel, "")


def sha1(path: Path) -> str:
    h = hashlib.sha1()
    with path.open("rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def cod_subsegments() -> list[tuple[int, str, int, str]]:
    """(vaddr, stem, span, kind) for every `cod` subsegment, in link order.

    `span` is the distance to the next subsegment, i.e. the exact `.text` size
    the object must occupy (function body + trailing nop alignment padding).
    `kind` is the splat subsegment type (`asm`/`c` = code, `textbin` = the raw
    `.text` header, `data`/`rodata`/`lit4`/`sdata`/`sbss`/`bss` = data).
    """
    text = (ROOT / "config" / "SCUS_974.72.yaml").read_text(encoding="utf-8")
    in_cod = False
    entries: list[tuple[int, str, str]] = []
    for line in text.splitlines():
        if re.match(r"^  - name: ", line):
            in_cod = line.strip().endswith("cod")
            continue
        if not in_cod:
            continue
        m = re.match(r"^\s+- \[0x([0-9A-Fa-f]+), (\w+), (\S+?)\]", line)
        if m:
            entries.append((int(m.group(1), 16), m.group(3), m.group(2)))
    out: list[tuple[int, str, int, str]] = []
    for i, (rom, name, kind) in enumerate(entries):
        if i + 1 >= len(entries):
            continue
        nxt = entries[i + 1][0]
        if not name.startswith("cod/"):
            continue
        out.append((ROM_BASE + rom, name[len("cod/"):], nxt - rom, kind))
    return out


def patch_linker_script(c_sources: dict[str, str]) -> str:
    """Strip splat's ALIGN(.,16) and pin each C object's span.

    splat inserts `. = ALIGN(., 16);` between output sections (padding the
    original does not have) and, for a C replacement, the compiler emits no
    trailing alignment `nop`s. Aligning the location counter to 8 right after a
    C object makes the linker fill exactly that padding with the section FILL
    value (0x00000000 == nop).
    """
    spans = {stem: (vaddr, span) for vaddr, stem, span, _k in cod_subsegments()}
    text = LD_SCRIPT.read_text(encoding="utf-8", errors="replace")
    out: list[str] = []
    for line in text.splitlines():
        if ". = ALIGN(., 16);" in line:
            continue
        out.append(line)
        m = re.match(r"^\s+build/asm/cod/([0-9A-Fa-f]+)\.o\(\.text\*\);", line)
        if m and m.group(1) in c_sources and m.group(1) in spans:
            vaddr, span = spans[m.group(1)]
            # The compiler emits no trailing alignment `nop`s; the original
            # function is followed by padding up to the next subsegment. Advance
            # the location counter by the exact remainder so the linker fills the
            # gap with the section FILL value (0x00000000 == nop).
            # NOTE: this must be a *relative* advance (`. = . + n`) - an absolute
            # `. = <vaddr>` assignment breaks the AT() LMA handling, and
            # `. = ALIGN(., 8)` is wrong for the handful of subsegments that are
            # only 4-byte aligned (e.g. 02E6D0, next at 0x12E704; it grew the
            # image by 4 bytes).
            obj = ROOT / "build" / "asm" / "cod" / f"{m.group(1)}.o"
            got = eegcc.section_sizes(obj).get(".text", 0)
            pad = span - got
            out.append(f"        /* span pinned for C object {m.group(1)}: "
                       f"{got:#x} + {pad:#x} pad = {span:#x} bytes, "
                       f"next {vaddr + span:#x} */")
            if pad > 0:
                out.append(f"        . = . + {pad:#x};")
    return "\n".join(out) + "\n"


def build_elf() -> int:
    c_sources = load_c_sources()
    refs = object_refs()
    missing = [r for r in refs if not to_source(r).exists()]
    n_c = sum(1 for r in refs if stem_of(r) in c_sources)
    print(f"{len(refs)} objects referenced by the linker script "
          f"({n_c} from C, {len(refs) - n_c} from asm)")
    if missing:
        print(f"  {len(missing)} with NO source:")
        for r in missing[:20]:
            print(f"    {r}")

    def build_one(obj_rel: str) -> tuple[str, str]:
        stem = stem_of(obj_rel)
        if stem in c_sources:
            return compile_object(obj_rel, c_sources[stem])
        return assemble(obj_rel)

    failures: list[tuple[str, str]] = []
    with concurrent.futures.ThreadPoolExecutor(max_workers=JOBS) as ex:
        for obj_rel, err in ex.map(build_one, refs):
            if err:
                failures.append((obj_rel, err))
    if failures:
        print(f"\n{len(failures)} build failures (showing up to 25):")
        for obj_rel, err in failures[:25]:
            print(f"  {obj_rel}: {err}")
        return 1
    print("build: OK")

    PATCHED_LD.write_text(patch_linker_script(c_sources), encoding="utf-8",
                          newline="\n")

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
    print(f"expected      {EXPECTED_SIZE} bytes  sha1 {EXPECTED_SHA1}")
    ok = got == EXPECTED_SHA1 and size == EXPECTED_SIZE
    print("HASH MATCH" if ok else "HASH MISMATCH")
    return 0 if ok else 2


JOBS = os.cpu_count() or 4


def main() -> int:
    global JOBS
    ap = argparse.ArgumentParser()
    ap.add_argument("--jobs", type=int, default=os.cpu_count() or 4)
    ap.add_argument("--check", action="store_true",
                    help="alias for the default behaviour (kept for `make check`)")
    ap.add_argument("--targets", action="store_true",
                    help="also assemble objdiff target objects into build/target/")
    ap.add_argument("--only", nargs="*", default=[],
                    help="build only these object stems")
    args = ap.parse_args()
    JOBS = args.jobs

    if args.only:
        c_sources = load_c_sources()
        failures = 0
        for stem in args.only:
            ref = next((r for r in object_refs() if stem_of(r) == stem), None)
            if ref is None:
                print(f"{stem}: not referenced by the linker script")
                failures += 1
                continue
            err = (compile_object(ref, c_sources[stem]) if stem in c_sources
                   else assemble(ref))[1]
            _, terr = assemble_target(ref)
            print(f"{stem}: {'OK' if not err else 'FAIL ' + err}")
            if terr:
                print(f"{stem}: target object failed: {terr}")
            failures += bool(err) + bool(terr)
        if not failures:
            print(f"diff:  .tools/objdiff/objdiff-cli.exe diff -p . -u cod/{args.only[0]} -o - --format json")
        return 1 if failures else 0

    if args.targets:
        refs = object_refs()
        with concurrent.futures.ThreadPoolExecutor(max_workers=JOBS) as ex:
            bad = [e for _, e in ex.map(assemble_target, refs) if e]
        print(f"targets: {len(refs) - len(bad)}/{len(refs)} objects "
              f"-> {TARGET_DIR.relative_to(ROOT)}")
        if bad:
            for b in bad[:5]:
                print(f"  {b}")

    return build_elf()


if __name__ == "__main__":
    sys.exit(main())
