#!/usr/bin/env python3
"""Progress report for the decompilation.

    python3 tools/report.py            # human readable
    python3 tools/report.py --json     # machine readable

`matched` = functions in config/c_sources.txt. Each one is verified byte-exact
by `tools/build.py` (the whole flat image must hash to the pinned SHA-1), so the
matched-byte count is a verified number, not an estimate.
"""
from __future__ import annotations

import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent


def data() -> dict:
    c_sources = build.load_c_sources()
    subs = build.cod_subsegments()
    spans = {stem: (vaddr, span) for vaddr, stem, span, _k in subs}
    code = [(v, s, sp) for v, s, sp, k in subs if k in ("asm", "c")]
    text_total = sum(sp for v, s, sp, k in subs if k in ("asm", "c", "textbin"))
    matched_bytes = 0
    funcs = []
    for stem, src in sorted(c_sources.items()):
        vaddr, span = spans.get(stem, (0, 0))
        matched_bytes += span
        funcs.append({"stem": stem, "address": f"0x{vaddr:08X}", "size": span,
                      "source": src})
    asm_funcs = sum(1 for _v, s, _sp in code if s not in c_sources)
    return {
        "functions_total": len(code),
        "functions_matched_c": len(c_sources),
        "functions_asm": asm_funcs,
        "text_bytes_total": text_total,
        "text_bytes_matched": matched_bytes,
        "matched_percent": round(100.0 * matched_bytes / text_total, 3) if text_total else 0.0,
        "functions": funcs,
    }


def main() -> int:
    d = data()
    if "--json" in sys.argv:
        print(json.dumps(d, indent=2))
        return 0
    print("Shadow of the Colossus (USA, SCUS_974.72) - progress")
    print(f"  functions (splat)     : {d['functions_total']}")
    print(f"  matched from C        : {d['functions_matched_c']}")
    print(f"  still assembly        : {d['functions_asm']}")
    print(f"  .text bytes total     : {d['text_bytes_total']} (0x{d['text_bytes_total']:X})")
    print(f"  .text bytes matched   : {d['text_bytes_matched']}")
    print(f"  matched               : {d['matched_percent']} %")
    print("  ---")
    for f in d["functions"]:
        print(f"    {f['address']}  {f['size']:>3}B  {f['stem']:<8} {f['source']}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
