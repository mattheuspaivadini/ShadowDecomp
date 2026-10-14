#!/usr/bin/env python3
"""Phase 3: sweep ee-gcc2.96 flag sets over the flag-pinning cases.

Runs inside WSL (needs `tools/cc/eegcc.sh` and `build/SCUS_974.72.rom`).

    python3 tools/phase3_pin.py                       # all flag sets
    python3 tools/phase3_pin.py --flags "-O2 -g2"     # one set
    python3 tools/phase3_pin.py --list
"""
from __future__ import annotations

import argparse
import json
import os
import shutil
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import matchcheck  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
EEGCC = ROOT / "tools" / "cc" / "eegcc.sh"
OUT = ROOT / "build" / "phase3"

# ee-gcc2.96's cc1 is a 32-bit binary: it cannot `stat` sources on /mnt/c
# (drvfs reports inode/mtime values that overflow the 32-bit stat buffer ->
# "Value too large for defined data type"). Sources are therefore staged into a
# native (ext4) work directory before compiling.
WORK = Path(os.environ.get("SOT_WORK", str(Path.home() / "shadowdecomp-work")))


def stage_sources() -> None:
    import filecmp

    for name in ("src", "include"):
        src_root = ROOT / name
        dst_root = WORK / name
        for p in src_root.rglob("*"):
            rel = p.relative_to(src_root)
            dst = dst_root / rel
            if p.is_dir():
                dst.mkdir(parents=True, exist_ok=True)
            else:
                if not dst.exists() or not filecmp.cmp(p, dst, shallow=False):
                    dst.parent.mkdir(parents=True, exist_ok=True)
                    shutil.copy2(p, dst)

# Cases written for flag pinning: name -> nothing else (the .s is the truth).
CASES = [
    "002FE0",  # int  f(void) { return 2; }
    "011FB8",  # int  f(void) { return -1; }
    "028B00",  # int  f(void) { return 0; }
    "0032F0",  # void f(void) { }
    "0128C0",  # int  f(int*,int*) { ... }
    "013088",  # int  f(int*)        { ... }
    "012908",  # char *f(void)       { return &D; }
    "012BD0",  # int  f(int,int)     { ... globals ... }
    "001A30",  # void f(int)         { D_sdata = ...; }   (gp-relative)
    "011D50",  # void f(void)        { D_data = 0; }      (absolute)
    "004E78",  # strength reduction: &arr[x*320]
]

# Cases whose C shape is not reproduced by the *default* compiler
# (ee-gcc2.96). All three ARE byte-exact with the alternate revision
# ee-gcc2.9-991111-01 (manifest token `cc=29`, docs/compiler.md 4.3), so they
# are kept out of this 2.96 flag sweep to leave the flag signal clean.
NON_MATCHING = {
    "009268": "matched only by the 2.9-991111 revision (lui/ori 0xFFFFFFFE); "
              "2.96 emits `li $v1,-2` for every C spelling tried",
    "0148B8": "matched only by the 2.9-991111 revision (order of the two `lui`s)",
    "014918": "matched only by the 2.9-991111 revision (allocation around the "
              "bounds check)",
}

FLAG_SETS: list[tuple[str, str]] = [
    ("O2", "-O2"),
    ("O1", "-O1"),
    ("O3", "-O3"),
    ("Os", "-Os"),
    ("O2g0", "-O2 -g0"),
    ("O2g", "-O2 -g"),
    ("O2g2", "-O2 -g2"),
    ("O2g3", "-O2 -g3"),
    ("O2G0", "-O2 -G0"),
    ("O2G8", "-O2 -G8"),
    ("O2G128", "-O2 -G128"),
    ("O2nogpopt", "-O2 -mno-gpopt"),
    ("O2G0nogpopt", "-O2 -G0 -mno-gpopt"),
    ("O2nocommon", "-O2 -fno-common"),
    ("O2soft", "-O2 -msoft-float"),
    ("O2G8g2", "-O2 -G8 -g2"),
    ("O2G0g2", "-O2 -G0 -g2"),
]


def compile_one(case: str, flags: str, outdir: Path) -> tuple[bool, str]:
    src = WORK / "src" / "cod" / f"{case}.c"
    obj = outdir / f"{case}.o"
    cmd = [str(EEGCC), "-c", *flags.split(), "-Iinclude", str(src), "-o", str(obj)]
    r = subprocess.run(cmd, capture_output=True, text=True, cwd=str(WORK))
    if r.returncode != 0:
        return False, (r.stderr or r.stdout).strip().splitlines()[0]
    return True, ""


def run_set(tag: str, flags: str, rom: bytes, verbose: bool) -> dict:
    outdir = WORK / "obj" / tag
    if outdir.exists():
        shutil.rmtree(outdir)
    outdir.mkdir(parents=True)
    results = []
    for case in CASES:
        ok, err = compile_one(case, flags, outdir)
        if not ok:
            results.append({"case": case, "ok": False, "why": f"compile failed: {err}"})
            continue
        results.append(matchcheck.compare(outdir / f"{case}.o", case, rom, verbose=verbose))
    n = sum(1 for r in results if r["ok"])
    return {"tag": tag, "flags": flags, "matched": n, "total": len(CASES),
            "results": results}


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--flags", default="")
    ap.add_argument("--tag", default="adhoc")
    ap.add_argument("--verbose", action="store_true")
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--json", type=Path, default=OUT / "results.json")
    args = ap.parse_args()

    if args.list:
        for tag, flags in FLAG_SETS:
            print(f"{tag:<14} {flags}")
        return 0

    rom = matchcheck.load_rom()
    stage_sources()
    sets = [(args.tag, args.flags)] if args.flags else FLAG_SETS
    summary = []
    for tag, flags in sets:
        r = run_set(tag, flags, rom, args.verbose)
        summary.append(r)
        marks = "".join("+" if x["ok"] else "." for x in r["results"])
        print(f"{tag:<14} {r['matched']:>2}/{r['total']}  {marks}   {flags}")
        if args.verbose:
            for x in r["results"]:
                if not x["ok"]:
                    print(f"    {x['case']}: {x.get('why','?')}")
                    for d in x.get("diffs", [])[:6]:
                        print(f"      +{d['off']:#04x} orig {d['orig']} mine {d['mine']}")
    args.json.parent.mkdir(parents=True, exist_ok=True)
    args.json.write_text(json.dumps(summary, indent=1), encoding="utf-8")
    print(f"cases in order: {' '.join(CASES)}")
    if NON_MATCHING:
        print("known non-matching (excluded from the sweep):")
        for c, why in NON_MATCHING.items():
            print(f"  {c}: {why}")
    print(f"wrote {args.json}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
