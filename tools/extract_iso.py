#!/usr/bin/env python3
"""Extract the PS2 ISO to extracted/ and write manifest/files.txt.

Reads the source ISO read-only (never modified), extracts every regular file
preserving the ISO tree, and records size + SHA-1 + MD5 for each file.

Usage:
    python tools/extract_iso.py <iso> <dest_dir> <manifest_out>
"""

from __future__ import annotations

import hashlib
import os
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from iso9660 import open_iso, walk, iter_files, SECTOR  # noqa: E402


def hash_file(path: str) -> tuple[int, str, str]:
    sha1 = hashlib.sha1()
    md5 = hashlib.md5()
    size = 0
    with open(path, "rb") as f:
        while True:
            chunk = f.read(1 << 20)
            if not chunk:
                break
            size += len(chunk)
            sha1.update(chunk)
            md5.update(chunk)
    return size, sha1.hexdigest(), md5.hexdigest()


def extract(iso: str, dest: str, manifest: str) -> None:
    f, root = open_iso(iso)
    try:
        walk(f, root, max_depth=10)
        entries = sorted(iter_files(root), key=lambda kv: kv[0])
        rows = []
        t0 = time.time()
        for rel, node in entries:
            rel = rel.lstrip("/")
            out = os.path.join(dest, rel.replace("/", os.sep))
            os.makedirs(os.path.dirname(out), exist_ok=True)
            if os.path.exists(out) and os.path.getsize(out) == node.size:
                pass  # already extracted
            else:
                with open(out, "wb") as out_f:
                    f.seek(node.lba * SECTOR)
                    remaining = node.size
                    buf = 1 << 20
                    while remaining > 0:
                        chunk = f.read(min(buf, remaining))
                        if not chunk:
                            raise RuntimeError(f"short read extracting {rel}")
                        out_f.write(chunk)
                        remaining -= len(chunk)
            size, sha1, md5 = hash_file(out)
            rows.append((rel, node.lba, node.size, sha1, md5))
            print(f"[ok] {rel}  size={node.size} sha1={sha1}")
    finally:
        f.close()

    os.makedirs(os.path.dirname(manifest), exist_ok=True)
    with open(manifest, "w", encoding="utf-8", newline="\n") as m:
        m.write("# Shadow of the Colossus (USA) — extracted file manifest\n")
        m.write(f"# source ISO: {os.path.basename(iso)}\n")
        m.write(f"# generated: {time.strftime('%Y-%m-%d %H:%M:%S')}\n")
        m.write("# fields: size_bytes  lba  sha1  md5  path\n")
        for rel, lba, size, sha1, md5 in rows:
            m.write(f"{size:>12}  {lba:>9}  {sha1}  {md5}  {rel}\n")
    print(f"wrote {manifest} ({len(rows)} files) in {time.time()-t0:.1f}s")


if __name__ == "__main__":
    if len(sys.argv) != 4:
        print(__doc__, file=sys.stderr)
        raise SystemExit(2)
    extract(sys.argv[1], sys.argv[2], sys.argv[3])
