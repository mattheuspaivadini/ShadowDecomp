#!/usr/bin/env python3
"""Compiler x function x flag-set match matrix (Session 4, step 1).

Compiles every reconstruction we have (the functions already byte-exact from C
AND the `src/non_matching/` attempts) with each installed EE-GCC distribution,
compares each object with the original bytes (`tools/matchcheck.py`), and prints
a matrix. Used to decide whether a different EE-GCC *revision* explains the
non-matching families.

Runs inside WSL2.

    python3 tools/cc_matrix.py --list-compilers
    python3 tools/cc_matrix.py                          # every Linux compiler, all cases
    python3 tools/cc_matrix.py --compilers ee-gcc2.96 ee-gcc3.2-040921
    python3 tools/cc_matrix.py --set nonmatching --verbose
"""
from __future__ import annotations

import argparse
import concurrent.futures
import json
import os
import shutil
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(Path(__file__).resolve().parent))
import build  # noqa: E402
import eegcc  # noqa: E402
import matchcheck  # noqa: E402

CC_DIR = ROOT / "tools" / "cc"
OUT = ROOT / "build" / "cc_matrix"

# Flag sets tried for every case. Tag -> flags (a leading list is added on top
# of the per-TU manifest flags used by the "matching" set).
FLAG_SETS = [
    ("pinned", None),          # -O2 -g2 -G8 (manifest per-TU flags when listed)
    ("g0", ["-O2", "-g0", "-G8"]),
]


# --------------------------------------------------------------------------
# compiler discovery
# --------------------------------------------------------------------------
def _is_linux_dist(d: Path) -> bool:
    for c in ("bin/ee-gcc", "bin/ee-gcc.bin"):
        p = d / c
        if p.exists():
            raw = p.read_bytes()[:4]
            if raw[:4] == b"\x7fELF":
                return True
            if raw[:2] == b"#!":           # bash wrapper (dtls13010)
                return True
    return False


def _is_pe_dist(d: Path) -> bool:
    return (d / "bin" / "ee-gcc.exe").exists()


def list_compilers(include_wine: bool = False) -> list[str]:
    """Linux (ELF i386) EE-GCC distributions in tools/cc/, plus (optionally)
    the Windows (PE) ones as `wine:<name>`."""
    if not CC_DIR.exists():
        return []
    out = []
    for d in sorted(CC_DIR.iterdir()):
        if d.is_dir() and d.name.startswith("ee-gcc"):
            if _is_linux_dist(d):
                out.append(d.name)
            elif include_wine and _is_pe_dist(d):
                out.append("wine:" + d.name)
    return out


def compiler_version(sel: str) -> str:
    if eegcc.is_wine(sel):
        drv = eegcc.wine_dist_dir(sel) / "bin" / "ee-gcc.exe"
        env = {**os.environ, "WINEDEBUG": "-all",
               "WINEPREFIX": eegcc.WINE_PREFIX}
        r = subprocess.run(["wine", str(drv), "--version"],
                           capture_output=True, text=True, env=env)
    else:
        r = subprocess.run([str(CC_DIR / "eegcc.sh"), "--version"],
                           capture_output=True, text=True,
                           env={**os.environ, "EE_GCC_DIR": sel})
    if r.returncode != 0:
        return "?"
    lines = (r.stdout or r.stderr).strip().splitlines()
    return lines[0] if lines else "?"


# --------------------------------------------------------------------------
# cases
# --------------------------------------------------------------------------
def matching_stems() -> list[str]:
    return sorted(build.load_c_sources())


def nonmatching_stems() -> list[str]:
    d = ROOT / "src" / "non_matching"
    if not d.exists():
        return []
    return sorted(p.stem for p in d.glob("*.c"))


def source_for(stem: str) -> str | None:
    if stem in build.load_c_sources():
        return build.load_c_sources()[stem]
    p = ROOT / "src" / "non_matching" / f"{stem}.c"
    if p.exists():
        return str(p.relative_to(ROOT)).replace("\\", "/")
    return None


# --------------------------------------------------------------------------
# compile + compare
# --------------------------------------------------------------------------
def compile_flags(stem: str, tag: str, override: list[str] | None) -> list[str]:
    if override is not None:
        base = list(override)
        # a per-TU `-g...` in the manifest must replace the override's -g
        per_tu = build.load_c_flags(stem)
        if any(f.startswith("-g") for f in per_tu):
            base = [f for f in base if not f.startswith("-g")] + per_tu
        return base
    return build.load_c_flags(stem)


def run_case(sel: str, stem: str, tag: str, override: list[str] | None,
             rom: bytes, verbose: bool) -> dict:
    src = source_for(stem)
    if src is None:
        return {"stem": stem, "ok": False, "why": "no source"}
    obj = OUT / sel / tag / f"{stem}.o"
    obj.parent.mkdir(parents=True, exist_ok=True)
    if obj.exists():
        obj.unlink()
    err = eegcc.compile_c(src, obj, compile_flags(stem, tag, override),
                          compiler=sel, stage=False)
    if err:
        return {"stem": stem, "ok": False, "why": f"compile: {err}"}
    r = matchcheck.compare(obj, stem, rom, verbose=verbose)
    return r


def probe_metadata(sel: str) -> dict:
    """e_flags + section names of an object built with `sel` (step 1.4)."""
    src = ROOT / "src" / "non_matching" / "0128D0.c"
    obj = OUT / sel / "meta.o"
    obj.parent.mkdir(parents=True, exist_ok=True)
    err = eegcc.compile_c(str(src.relative_to(ROOT)).replace("\\", "/"), obj,
                          ["-O2", "-g2", "-G8"], compiler=sel)
    if err:
        return {"compiler": sel, "error": err}
    data = obj.read_bytes()
    e_flags, = struct.unpack_from("<I", data, 0x24)
    e_shoff, = struct.unpack_from("<I", data, 0x20)
    e_shentsize, e_shnum, e_shstrndx = struct.unpack_from("<HHH", data, 0x2E)
    shs = [struct.unpack_from("<10I", data, e_shoff + i * e_shentsize)
           for i in range(e_shnum)]
    shstr = data[shs[e_shstrndx][4]:shs[e_shstrndx][4] + shs[e_shstrndx][5]]

    def nm(off: int) -> str:
        end = shstr.find(b"\0", off)
        return shstr[off:end].decode("utf-8", "replace")

    sections = [nm(sh[0]) for sh in shs]
    comment = b""
    for sh, name in zip(shs, sections):
        if name == ".comment":
            comment = data[sh[4]:sh[4] + sh[5]]
    return {
        "compiler": sel,
        "version": compiler_version(sel),
        "e_flags": f"0x{e_flags:08X}",
        "sections": sections,
        "has_mdebug": any(s.startswith(".mdebug") for s in sections),
        "comment": comment.decode("utf-8", "replace").replace("\0", " | ").strip(" |"),
    }


# --------------------------------------------------------------------------
def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--compilers", nargs="*", default=None)
    ap.add_argument("--set", dest="case_set",
                    choices=["matching", "nonmatching", "all"],
                    default="all")
    ap.add_argument("--cases", nargs="*", default=None)
    ap.add_argument("--list-compilers", action="store_true")
    ap.add_argument("--wine", action="store_true",
                    help="also test the Windows (PE) distributions via wine")
    ap.add_argument("--metadata", action="store_true",
                    help="also dump e_flags/sections/.comment per compiler")
    ap.add_argument("--verbose", action="store_true")
    ap.add_argument("--jobs", type=int, default=os.cpu_count() or 4)
    ap.add_argument("--json", type=Path, default=OUT / "matrix.json")
    args = ap.parse_args()

    compilers = args.compilers or list_compilers(include_wine=args.wine)
    if args.list_compilers:
        for c in compilers:
            print(f"{c:<32} {compiler_version(c)}")
        return 0

    if args.cases:
        cases = args.cases
    elif args.case_set == "matching":
        cases = matching_stems()
    elif args.case_set == "nonmatching":
        cases = nonmatching_stems()
    else:
        cases = sorted(set(matching_stems()) | set(nonmatching_stems()))

    rom = matchcheck.load_rom()
    OUT.mkdir(parents=True, exist_ok=True)
    if args.verbose:
        for tag, _ in FLAG_SETS:
            p = OUT / tag
            if p.exists():
                shutil.rmtree(p)

    # stage src/ + include/ once (cc1 cannot stat /mnt/c), then compile in
    # parallel - the per-call re-stage of eegcc.compile_c would dominate.
    eegcc.stage_sources()

    result: dict = {"cases": cases, "flag_sets": [t for t, _ in FLAG_SETS],
                    "compilers": {}, "metadata": []}

    tasks = {}
    with concurrent.futures.ThreadPoolExecutor(max_workers=args.jobs) as ex:
        for sel in compilers:
            result["compilers"][sel] = {"version": compiler_version(sel),
                                        "cases": {s: {} for s in cases}}
            for stem in cases:
                for tag, override in FLAG_SETS:
                    fut = ex.submit(run_case, sel, stem, tag, override, rom,
                                    args.verbose)
                    tasks[fut] = (sel, stem, tag)
        if args.metadata:
            for sel in compilers:
                fut = ex.submit(probe_metadata, sel)
                tasks[fut] = ("__meta__", sel, None)
        for fut in concurrent.futures.as_completed(tasks):
            sel, stem, tag = tasks[fut]
            r = fut.result()
            if sel == "__meta__":
                result["metadata"].append(r)
            else:
                result["compilers"][sel]["cases"][stem][tag] = {
                    "ok": r.get("ok", False),
                    "why": r.get("why", ""),
                    "diffs": len(r.get("diffs", [])),
                    "code_size": r.get("code_size", 0),
                    "compiled_size": r.get("compiled_size", 0),
                }

    # ---- print matrix -----------------------------------------------------
    print(f"\ncases: {len(cases)}  compilers: {len(compilers)}  "
          f"flag sets: {[t for t, _ in FLAG_SETS]}")
    for tag, _ in FLAG_SETS:
        print(f"\n== flag set '{tag}'")
        header = "case        " + "".join(f"{c[:22]:>24}" for c in compilers)
        print(header)
        for stem in cases:
            row = f"{stem:<12}"
            for sel in compilers:
                c = result["compilers"][sel]["cases"][stem][tag]
                if c["ok"]:
                    cell = "MATCH"
                elif c["why"].startswith("compile"):
                    cell = "CFAIL"
                elif c["diffs"]:
                    cell = f"-{c['diffs']}"
                else:
                    cell = f"S{c['compiled_size'] - c['code_size']:+d}"
                row += f"{cell:>24}"
            print(row)
        tot = {sel: sum(1 for s in cases
                        if result["compilers"][sel]["cases"][s][tag]["ok"])
               for sel in compilers}
        print("TOTAL       " + "".join(f"{tot[c]:>24}" for c in compilers))

    print("\ncompiler versions:")
    for sel in compilers:
        print(f"  {sel:<32} {result['compilers'][sel]['version']}")
        if args.metadata:
            for m in result["metadata"]:
                if m.get("compiler") == sel:
                    print(f"      e_flags={m.get('e_flags')} "
                          f"mdebug={m.get('has_mdebug')} "
                          f"comment={m.get('comment')!r}")
                    print(f"      sections={m.get('sections')}")

    args.json.parent.mkdir(parents=True, exist_ok=True)
    args.json.write_text(json.dumps(result, indent=1), encoding="utf-8")
    print(f"\nwrote {args.json}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
