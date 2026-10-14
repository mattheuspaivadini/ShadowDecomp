#!/usr/bin/env python3
"""Build one function and print its diff against the original (Phase 6 loop).

    python3 tools/diff_func.py func_001128C0
    python3 tools/diff_func.py 0128C0
    python3 tools/diff_func.py func_001128C0 --objdiff    # raw objdiff JSON
    python3 tools/diff_func.py func_001128C0 --no-objdiff

Steps: (1) rebuild the function's object (C if `config/c_sources.txt` lists it,
otherwise its `.s`) and its objdiff target object, (2) ask objdiff-cli for the
match percentage, (3) if it is not a match, print the exact instruction
differences from tools/matchcheck.py.

Runs the build in WSL2; uses the Windows objdiff-cli for step 2.
"""
from __future__ import annotations

import json
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
OBJDIFF = ROOT / ".tools" / "objdiff" / "objdiff-cli.exe"
COD = ROOT / "asm" / "cod"

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build  # noqa: E402
import matchcheck  # noqa: E402


def resolve(arg: str) -> tuple[str, str]:
    """argument -> (stem, symbol), using the splat .s files as the index."""
    stem = arg.split("/")[-1]
    if stem.startswith(("func_", "D_")):
        for p in sorted(COD.glob("*.s")):
            for line in p.read_text(encoding="utf-8", errors="replace").splitlines():
                if line.startswith("glabel "):
                    if line.split()[1] == stem:
                        return p.stem, stem
                    break
        raise SystemExit(f"function not found: {arg}")
    p = COD / f"{stem}.s"
    if not p.exists():
        raise SystemExit(f"no such function file: {p}")
    for line in p.read_text(encoding="utf-8", errors="replace").splitlines():
        if line.startswith("glabel "):
            return stem, line.split()[1]
    raise SystemExit(f"no glabel in {p}")


def objdiff_percent(stem: str, symbol: str) -> None:
    if not OBJDIFF.exists():
        print("objdiff-cli not present; skipping the objdiff check")
        return
    run = subprocess.run([str(OBJDIFF), "diff", "-p", ".", "-u", f"cod/{stem}",
                          "-o", "-", "--format", "json"],
                         capture_output=True, text=True, cwd=str(ROOT))
    if run.returncode != 0 or not run.stdout.strip():
        err = run.stderr.strip().splitlines()
        print(f"objdiff-cli failed: {err[0] if err else run.returncode}")
        return
    if "--objdiff" in sys.argv:
        print(run.stdout)
        return
    data = json.loads(run.stdout)
    for side, label in (("right", "base (ours)"), ("left", "target     ")):
        for s in data.get(side, {}).get("symbols", []):
            if s.get("name") == symbol and "match_percent" in s:
                print(f"objdiff {label}: {s['match_percent']}% match")


def main() -> int:
    argv = [a for a in sys.argv[1:] if not a.startswith("--")]
    flags = {a for a in sys.argv[1:] if a.startswith("--")}
    if not argv:
        print(__doc__)
        return 2
    stem, symbol = resolve(argv[0])
    c_sources = build.load_c_sources()
    in_c = stem in c_sources
    print(f"== {symbol}  (stem {stem}, "
          f"{'C: ' + c_sources[stem] if in_c else 'assembly only'})")

    cmd = (f"cd /mnt/c/Users/Matheus/Documents/ShadowDecomp && "
           f"python3 tools/build.py --only {stem} 2>&1 | tail -3")
    r = subprocess.run(["wsl", "-d", "Ubuntu", "-u", "root", "--", "bash", "-lc", cmd],
                       capture_output=True, text=True, cwd=str(ROOT))
    sys.stdout.write(r.stdout)
    if r.returncode != 0:
        sys.stdout.write(r.stderr)

    if "--no-objdiff" not in flags:
        objdiff_percent(stem, symbol)

    if in_c:
        obj = ROOT / "build" / "asm" / "cod" / f"{stem}.o"
        if obj.exists():
            res = matchcheck.compare(obj, stem, matchcheck.load_rom(), verbose=True)
            if not res["ok"]:
                print(f"  bytes: {res.get('why', 'differs')}")
                for rl in res.get("relocs", []):
                    print(f"    reloc +{rl['off']:#04x} {rl['type']:<8} {rl['sym']}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
