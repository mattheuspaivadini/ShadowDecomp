#!/usr/bin/env python3
"""Compile one scratch C draft for an .XFF stem and diff it against the container.

`tools/xffcheck.py` gates the *lane* (`overlays/<mod>/src/*.c` + manifest). This
tool is the exploration counterpart: it takes any scratch source, compiles it with
the pinned EE-GCC and scores it against the original bytes with the relocations
masked, without touching `overlays/` or `c_sources.txt`. It is what the template
search (`tools/xff_try_shapes.py`) and the hand-written drafts use for the fast
iteration loop.

Usage (inside WSL, like every ee-gcc step):
    python3 tools/xff_try.py KERNEL 012940 /tmp/draft.c
    python3 tools/xff_try.py KERNEL 012940 /tmp/draft.c -G0 --verbose
    python3 tools/xff_try.py KERNEL 012940 --size 0x0c /tmp/draft.c
    python3 tools/xff_try.py KERNEL 003d20 -            # source on stdin

Exit code 0 when the draft is byte-exact.
"""
from __future__ import annotations

import argparse
import struct
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import eegcc  # noqa: E402
import xffcheck  # noqa: E402
import xfflib  # noqa: E402


def score(module: str, mod: dict, stem: str, c_text: str, *, flags: list[str],
          size: int | None, symbol: str | None, verbose: bool, cc: str | None = None) -> dict:
    off = int(stem, 16)
    fn = xfflib.func_bounds(mod, off)
    if fn is not None:
        start, end, name = fn
        fsize = end - start
    elif size:
        start, fsize, name = off, size, symbol or f"func_{stem.upper()}"
    else:
        raise SystemExit(f"{stem}: no symbol at 0x{off:06x}; pass --size")

    tmp = Path(tempfile.mkdtemp(dir=str(Path(eegcc.WORK) / "xff_try"),
                               prefix=f"{module}_{stem}_"))
    src = tmp / "draft.c"
    src.write_text(c_text, encoding="utf-8")
    obj = tmp / "draft.o"
    err = eegcc.compile_c(str(src), obj, flags, compiler=cc, stage=False)
    if err:
        return {"ok": False, "why": f"compile: {err}"}

    objd = xffcheck.eegcc_object(obj)
    sym = xffcheck.find_symbol(objd, name)
    if sym is None:
        have = [s["name"] for s in objd["symbols"].values() if s["type"] == 2]
        return {"ok": False, "why": f"object defines no symbol {name} (has {have})"}
    ostart = sym["value"]
    mine = objd["text"][ostart:ostart + fsize]
    orig = mod["text"][start:start + fsize]
    msize = sym.get("size") or len(mine)
    tail = objd["text"][ostart + fsize:ostart + msize]
    if msize > fsize and not any(tail):
        msize = fsize  # st_size counts trailing alignment nops
    if verbose and msize != fsize:
        # raw words of both sides (WSL has no rabbitizer; decode with tools/xff_dis.py's decoder)
        whole = objd["text"][ostart:ostart + msize]
        for i in range(0, max(fsize, msize), 4):
            a = orig[i:i + 4].hex() if i < fsize else "--------"
            b = whole[i:i + 4].hex() if i < msize else "--------"
            print(f"    = +{i:#05x}  orig {a}  mine {b}")
    if len(mine) != fsize or msize != fsize:
        return {"ok": False, "why": f"size differs: original {fsize} B, "
                                    f"compiled {len(mine)} B"}

    masks = [a | b for a, b in zip(
        xfflib.mask_for(mod["relocs"], start, fsize),
        xffcheck._obj_masks(objd, ostart, fsize))]
    diffs = []
    for i in range(0, fsize, 4):
        a, = struct.unpack_from("<I", orig, i)
        b, = struct.unpack_from("<I", mine, i)
        if (a ^ b) & ~masks[i // 4]:
            diffs.append((i, a, b))
    if verbose:
        for i, a, b in diffs:
            print(f"    ! +{i:#05x}  orig {a:08X}  mine {b:08X}")
    return {"ok": not diffs, "name": name, "size": fsize, "diffs": diffs,
            "why": "" if not diffs else f"{len(diffs)} of {fsize // 4} words differ"}


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("module")
    ap.add_argument("stem")
    ap.add_argument("source", help="scratch .c path, or - for stdin")
    ap.add_argument("--size", default=None, help="size for an unnamed function")
    ap.add_argument("--symbol", default=None, help="symbol name for an unnamed one")
    ap.add_argument("--flags", default="-G0", help="extra compiler flags (quoted)")
    ap.add_argument("--verbose", action="store_true")
    ap.add_argument("--cc", default=None, help="compiler token, as cc= in c_sources.txt")
    args = ap.parse_args()
    flags = args.flags.split()

    c_text = (sys.stdin.read() if args.source == "-"
              else Path(args.source).read_text(encoding="utf-8"))
    mod = xfflib.load_module(args.module.upper())
    (Path(eegcc.WORK) / "xff_try").mkdir(parents=True, exist_ok=True)
    r = score(args.module.upper(), mod, (args.stem.lower().removeprefix("0x") or "0"), c_text,
              flags=flags, size=int(args.size, 0) if args.size else None,
              symbol=args.symbol, verbose=args.verbose, cc=args.cc)
    if r["ok"]:
        print(f"MATCH {args.stem} {r['name']} ({r['size']} B)")
        return 0
    print(f"DIFF  {args.stem} {r.get('name', '?')}: {r['why']}")
    return 1


if __name__ == "__main__":
    sys.exit(main())
