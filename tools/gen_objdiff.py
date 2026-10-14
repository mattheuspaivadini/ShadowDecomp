#!/usr/bin/env python3
"""Generate `objdiff.json` for objdiff-cli (Phase 2 infrastructure).

One unit per function that has a matching C source. The *target* object is the
original splat assembly assembled into an object (`build/target/asm/cod/...`,
produced by `tools/build.py --targets`), the *base* object is what this project
compiles (`build/asm/cod/...`).

    python3 tools/gen_objdiff.py            # write objdiff.json
    objdiff-cli diff -p . -u cod/002FE0 -o - --format json
    objdiff-cli report -p . -o report.json
"""
from __future__ import annotations

import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
OUT = ROOT / "objdiff.json"


def main() -> int:
    c_sources = build.load_c_sources()
    spans = {stem: (vaddr, span) for vaddr, stem, span in build.cod_subsegments()}
    units = []
    for stem, src in sorted(c_sources.items()):
        vaddr, span = spans.get(stem, (0, 0))
        units.append({
            "name": f"cod/{stem}",
            "target_path": f"build/target/asm/cod/{stem}.o",
            "base_path": f"build/asm/cod/{stem}.o",
            "metadata": {
                "complete": True,
                "source_path": src,
                # evidence, not objdiff input
                "address": f"0x{vaddr:08X}" if vaddr else "?",
                "size": f"0x{span:X}" if span else "?",
            },
        })
    cfg = {
        "min_version": "2.0.0",
        "custom_make": "make",
        "build_base": False,
        "build_target": False,
        "watch_patterns": ["*.c", "*.h", "*.s"],
        "units": units,
    }
    OUT.write_text(json.dumps(cfg, indent=2) + "\n", encoding="utf-8")
    print(f"wrote {OUT.relative_to(ROOT)} with {len(units)} unit(s)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
