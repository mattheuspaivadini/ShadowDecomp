#!/usr/bin/env python3
"""Byte-exact verifier for .XFF overlay functions (KERNEL / MANAGER / GAMECORE).

The overlay modules are *relocatable* images, so the gate is:

  compile the C source with the pinned EE-GCC  ->  compare the function's `.text`
  bytes against the original container bytes, with every field patched by a
  relocation masked out (the linker, not the compiler, decides those).

That is the same rule `tools/matchcheck.py` applies to the boot ELF; here the
reference bytes come from the `.XFF` module and the masks come from the union of
the original `.rel.text` entries and the compiled object's own relocations.

Sources live in `overlays/<module>/src/<stem>.c` and are listed (with optional
`cc=` / flag overrides) in `overlays/<module>/c_sources.txt`.

Usage:
    python tools/xffcheck.py --list KERNEL --small 40
    python tools/xffcheck.py KERNEL 000490 0007a8      # verify named stems
    python tools/xffcheck.py KERNEL                    # verify the whole list
"""
from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import eegcc  # noqa: E402
import xfflib  # noqa: E402

OVERLAYS = ROOT / "overlays"


def parse_manifest(module: str) -> dict[str, dict]:
    """Read overlays/<module>/c_sources.txt -> {stem: {source, cc, flags}}."""
    path = OVERLAYS / module.lower() / "c_sources.txt"
    out: dict[str, dict] = {}
    if not path.exists():
        return out
    for line in path.read_text(encoding="utf-8").splitlines():
        line = line.split("#", 1)[0].strip()
        if not line or "=" not in line:
            continue
        stem, rest = line.split("=", 1)
        parts = rest.split()
        entry = {"source": parts[0], "cc": None, "flags": []}
        for p in parts[1:]:
            if p.startswith("cc="):
                entry["cc"] = p[3:]
            elif p:
                entry["flags"].append(p)
        out[stem.strip().lower()] = entry
    return out


def func_by_stem(mod: dict, stem: str) -> dict | None:
    off = int(stem, 16)
    for s in mod["functions"]:
        if s["st_value"] == off:
            return s
    return None


def find_symbol(obj: dict, name: str) -> dict | None:
    for s in obj["symbols"].values():
        if s["name"] == name and s["type"] == 2:
            return s
    return None


def compare(module: str, mod: dict, stem: str, entry: dict, *,
            verbose: bool = False) -> dict:
    fn = func_by_stem(mod, stem)
    if fn is None:
        return {"stem": stem, "ok": False, "why": f"no function at 0x{int(stem, 16):06x}"}
    start, size, name = fn["st_value"], fn["size"], fn["name"]
    orig = mod["text"][start:start + size]

    src = OVERLAYS / module.lower() / entry["source"]
    if not src.exists():
        return {"stem": stem, "name": name, "ok": False, "why": f"missing {src}"}

    objp = eegcc.WORK / "obj" / "xff" / module.lower() / f"{stem}.o"
    objp.parent.mkdir(parents=True, exist_ok=True)
    err = eegcc.compile_c(str(src.relative_to(ROOT)), objp, entry["flags"],
                          compiler=entry["cc"], stage=False)
    if err:
        return {"stem": stem, "name": name, "ok": False, "why": f"compile: {err}"}

    obj = eegcc_object(objp)
    sym = find_symbol(obj, name)
    if sym is None:
        return {"stem": stem, "name": name, "ok": False,
                "why": f"{objp.name} defines no symbol {name}"}
    ostart = sym["value"]
    mine = obj["text"][ostart:ostart + size]

    res = {"stem": stem, "name": name, "addr": start, "orig_size": size,
           "compiled_size": len(obj["text"]) - ostart, "ok": False, "diffs": []}
    if len(mine) != len(orig):
        res["why"] = f"size differs: original {size} B, compiled {len(mine)} B"
        return res

    masks = [a | b for a, b in zip(
        xfflib.mask_for(mod["relocs"], start, size),
        _obj_masks(obj, ostart, size))]
    diffs = []
    for i in range(0, size, 4):
        a, = struct.unpack_from("<I", orig, i)
        b, = struct.unpack_from("<I", mine, i)
        if (a ^ b) & ~masks[i // 4]:
            diffs.append((i, a, b))
    res["diffs"] = [{"off": i, "orig": f"{a:08X}", "mine": f"{b:08X}"} for i, a, b in diffs]
    res["ok"] = not diffs
    if diffs:
        res["why"] = f"{len(diffs)} instruction(s) differ"
        if verbose:
            for d in res["diffs"]:
                print(f"    ! +{d['off']:#04x}  orig {d['orig']}  mine {d['mine']}")
    return res


def _obj_masks(obj: dict, start: int, size: int) -> list[int]:
    masks = [0] * ((size + 3) // 4)
    for off, typ, _si in obj["relocs"]:
        off -= start
        if 0 <= off < size:
            masks[off // 4] |= xfflib.REL_FIELD.get(typ, ("", 0))[1]
    return masks


def eegcc_object(path: Path) -> dict:
    """Minimal ELF32 reader: .text, symbols and .rel.text (like matchcheck)."""
    data = path.read_bytes()
    by_name = _sections(data)
    text = b""
    if ".text" in by_name:
        sh = by_name[".text"]
        text = data[sh[4]:sh[4] + sh[5]]
    symbols: dict[int, dict] = {}
    if ".symtab" in by_name and ".strtab" in by_name:
        sym_sh, str_sh = by_name[".symtab"], by_name[".strtab"]
        strtab = data[str_sh[4]:str_sh[4] + str_sh[5]]
        for i in range(sym_sh[5] // sym_sh[9]):
            o = sym_sh[4] + i * sym_sh[9]
            st_name, st_value, st_size, st_info, _oth, st_shndx = struct.unpack_from(
                "<IIIBBH", data, o)
            end = strtab.find(b"\0", st_name)
            symbols[i] = {"name": strtab[st_name:end].decode("utf-8", "replace"),
                          "value": st_value, "size": st_size,
                          "type": st_info & 0xF, "shndx": st_shndx}
    relocs = []
    if ".rel.text" in by_name:
        sh = by_name[".rel.text"]
        for o in range(sh[4], sh[4] + sh[5], 8):
            r_off, r_info = struct.unpack_from("<II", data, o)
            relocs.append((r_off, r_info & 0xFF, r_info >> 8))
    return {"text": text, "symbols": symbols, "relocs": relocs}


def _sections(data: bytes) -> dict[str, tuple]:
    """Section header tuples keyed by name (index 0 = name, 4/5 = offset/size)."""
    e_shoff, = struct.unpack_from("<I", data, 0x20)
    e_shentsize, e_shnum, e_shstrndx = struct.unpack_from("<HHH", data, 0x2E)
    shs = [struct.unpack_from("<10I", data, e_shoff + i * e_shentsize)
           for i in range(e_shnum)]
    strtab = shs[e_shstrndx]
    shstr = data[strtab[4]:strtab[4] + strtab[5]]
    out = {}
    for sh in shs:
        end = shstr.find(b"\0", sh[0])
        out[shstr[sh[0]:end].decode("utf-8", "replace")] = sh
    return out


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("module")
    ap.add_argument("stems", nargs="*")
    ap.add_argument("--list", action="store_true", help="list functions and exit")
    ap.add_argument("--small", type=int, default=0, metavar="N",
                    help="with --list: only the N smallest functions")
    ap.add_argument("--all", action="store_true", help="verify every manifest entry")
    ap.add_argument("--verbose", action="store_true")
    args = ap.parse_args()

    module = args.module.upper()
    mod = xfflib.load_module(module)
    manifest = parse_manifest(module)

    if args.list:
        funcs = mod["functions"]
        if args.small:
            funcs = sorted(funcs, key=lambda s: (s["size"], s["st_value"]))[:args.small]
        for s in funcs:
            stem = f"{s['st_value']:06x}"
            mark = "C" if stem in manifest else " "
            print(f"{mark} {stem}  {s['size']:5d}  {s['name']}")
        return 0

    stems = []
    for s in args.stems:
        s = s.lower()
        if s.startswith("0x"):
            s = s[2:]
        stems.append(s)
    if not stems or args.all:
        stems = sorted(manifest)
    if not stems:
        print("no stems to verify (manifest empty)")
        return 1

    eegcc.stage_sources()
    ok = 0
    total_bytes = 0
    for stem in stems:
        entry = manifest.get(stem)
        if entry is None:
            print(f"SKIP  {stem}: not in overlays/{module.lower()}/c_sources.txt")
            continue
        r = compare(module, mod, stem, entry, verbose=args.verbose)
        total_bytes += r.get("orig_size", 0)
        if r["ok"]:
            ok += 1
            print(f"MATCH {stem} {r['name']} ({r['orig_size']} B)")
        else:
            print(f"DIFF  {stem} {r.get('name', '?')}: {r.get('why', '')}")
    print(f"-- {ok}/{len(stems)} byte-exact ({total_bytes} B of .text)")
    return 0 if ok == len(stems) else 1


if __name__ == "__main__":
    sys.exit(main())
