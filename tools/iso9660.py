#!/usr/bin/env python3
"""Minimal, dependency-free ISO9660 reader for PS2 disc images.

Why this exists
---------------
The discovery step found no 7z / isoinfo / xorriso on this machine, so ISO9660
parsing is done in pure Python. This module only reads directory structures and
raw extents; it never writes to the source image.

ISO9660 essentials used here
----------------------------
* Logical sector size is 2048 bytes.
* The Primary Volume Descriptor (PVD) lives at logical sector 16 (offset 0x8000).
  Its first byte is 0x01 and bytes 1..5 are the ASCII magic "CD001".
* The root directory record is a 34-byte directory record at offset 156 of the PVD.
* A directory record layout (ECMA-119 9.1):
      offset 0  : uint8   record length (0 => padding to next sector)
      offset 1  : uint8   extended attribute length
      offset 2  : uint32  extent LBA, little-endian
      offset 6  : uint32  extent LBA, big-endian
      offset 10 : uint32  data length, little-endian
      offset 14 : uint32  data length, big-endian
      offset 18 : 7 bytes recording date/time
      offset 25 : uint8   file flags (bit1 = directory)
      offset 26 : uint8   file unit size
      offset 27 : uint8   interleave gap
      offset 28 : uint32  volume sequence number (both-endian pair)
      offset 32 : uint8   file identifier length
      offset 33 : bytes   file identifier
* Identifiers are padded to an even length; files carry a ";1" version suffix
  which is stripped here. Directories use a single 0x00 or 0x01 byte.
"""

from __future__ import annotations

import os
import sys
import struct
from dataclasses import dataclass, field

SECTOR = 2048
PVD_SECTOR = 16


@dataclass
class IsoNode:
    name: str
    lba: int
    size: int
    is_dir: bool
    children: list["IsoNode"] = field(default_factory=list)


class IsoError(Exception):
    pass


def _u32le(buf: bytes, off: int) -> int:
    return struct.unpack_from("<I", buf, off)[0]


def _u32be(buf: bytes, off: int) -> int:
    return struct.unpack_from(">I", buf, off)[0]


def _check_both_endian(buf: bytes, off: int) -> int:
    le = _u32le(buf, off)
    be = _u32be(buf, off + 4)
    if le != be:
        # Not fatal for reading, but worth surfacing for weird images.
        raise IsoError(f"both-endian mismatch at {off}: le={le:#x} be={be:#x}")
    return le


def _read_sector(f, lba: int, count: int = 1) -> bytes:
    f.seek(lba * SECTOR)
    data = f.read(SECTOR * count)
    if len(data) < SECTOR:
        raise IsoError(f"short read at LBA {lba}")
    return data


def _parse_dir_record(rec: bytes) -> IsoNode | None:
    length = rec[0]
    if length == 0:
        return None
    if len(rec) < 34:
        raise IsoError("directory record too short")
    lba = _u32le(rec, 2)
    size = _u32le(rec, 10)
    flags = rec[25]
    id_len = rec[32]
    ident = rec[33:33 + id_len]
    is_dir = bool(flags & 0x02)

    if id_len == 1 and ident in (b"\x00", b"\x01"):
        # "." or ".." entries.
        name = "." if ident == b"\x00" else ".."
        return IsoNode(name=name, lba=lba, size=size, is_dir=is_dir)

    # File identifiers are ASCII, possibly with a ";1" version suffix.
    name = ident.decode("latin-1")
    name = name.split(";", 1)[0]
    return IsoNode(name=name, lba=lba, size=size, is_dir=is_dir)


def _read_directory(f, node: IsoNode, depth: int, max_depth: int) -> list[IsoNode]:
    """Read the directory extent of `node` and return direct children."""
    if node.size == 0:
        return []
    sectors = (node.size + SECTOR - 1) // SECTOR
    data = _read_sector(f, node.lba, sectors)
    data = data[:node.size]

    children: list[IsoNode] = []
    off = 0
    while off < len(data):
        rec_len = data[off]
        if rec_len == 0:
            # Skip to the next sector boundary.
            off = ((off // SECTOR) + 1) * SECTOR
            continue
        rec = data[off:off + rec_len]
        node_child = _parse_dir_record(rec)
        off += rec_len
        if node_child is None:
            continue
        if node_child.name in (".", ".."):
            continue
        children.append(node_child)
        if node_child.is_dir and depth < max_depth:
            node_child.children = _read_directory(f, node_child, depth + 1, max_depth)
    return children


def open_iso(path: str):
    f = open(path, "rb")
    pvd = _read_sector(f, PVD_SECTOR)
    if pvd[0] != 0x01 or pvd[1:6] != b"CD001":
        f.close()
        raise IsoError("not an ISO9660 image (no PVD magic at sector 16)")
    root_rec = pvd[156:156 + 34]
    root = _parse_dir_record(root_rec)
    if root is None or not root.is_dir:
        f.close()
        raise IsoError("could not parse root directory record")
    return f, root


def walk(f, root: IsoNode, max_depth: int = 8) -> IsoNode:
    root.children = _read_directory(f, root, 0, max_depth)
    return root


def iter_files(root: IsoNode):
    stack = [(root, "")]
    while stack:
        node, prefix = stack.pop()
        if node.is_dir:
            for c in node.children:
                stack.append((c, prefix + node.name + "/" if node.name not in (".", "") else prefix))
        else:
            yield prefix + node.name, node


def read_extent(f, node: IsoNode) -> bytes:
    f.seek(node.lba * SECTOR)
    return f.read(node.size)


def extract_all(f, root: IsoNode, dest: str) -> int:
    """Extract every regular file preserving the ISO directory tree."""
    os.makedirs(dest, exist_ok=True)
    count = 0
    for rel, node in iter_files(root):
        rel = rel.lstrip("/")
        out = os.path.join(dest, rel.replace("/", os.sep))
        os.makedirs(os.path.dirname(out), exist_ok=True)
        with open(out, "wb") as out_f:
            f.seek(node.lba * SECTOR)
            remaining = node.size
            while remaining > 0:
                chunk = f.read(min(1 << 20, remaining))
                if not chunk:
                    break
                out_f.write(chunk)
                remaining -= len(chunk)
        count += 1
    return count


def find(root: IsoNode, name: str) -> list[str]:
    name_l = name.lower()
    return [rel for rel, _ in iter_files(root) if os.path.basename(rel).lower() == name_l]


def _main(argv: list[str]) -> int:
    if len(argv) < 3:
        print("usage: iso9660.py <list|tree|find|cat> <iso> [name]", file=sys.stderr)
        return 2
    cmd, iso = argv[1], argv[2]
    f, root = open_iso(iso)
    try:
        walk(f, root, max_depth=10)
        if cmd == "list":
            for rel, node in iter_files(root):
                print(f"{node.size:>12}  {node.lba:>9}  {rel.lstrip('/')}")
        elif cmd == "tree":
            def show(n: IsoNode, prefix: str):
                print(f"{prefix}{n.name}{'/' if n.is_dir else ''}  ({n.size})")
                for c in n.children:
                    show(c, prefix + "  ")
            show(root, "")
        elif cmd == "find":
            if len(argv) < 4:
                print("usage: iso9660.py find <iso> <name>", file=sys.stderr)
                return 2
            for m in find(root, argv[3]):
                print(m)
        elif cmd == "cat":
            if len(argv) < 4:
                print("usage: iso9660.py cat <iso> <path>", file=sys.stderr)
                return 2
            target = argv[3].lstrip("/").lower()
            for rel, node in iter_files(root):
                if rel.lstrip("/").lower() == target:
                    sys.stdout.buffer.write(read_extent(f, node))
                    return 0
            print(f"not found: {argv[3]}", file=sys.stderr)
            return 1
        else:
            print(f"unknown command: {cmd}", file=sys.stderr)
            return 2
    finally:
        f.close()
    return 0


if __name__ == "__main__":
    raise SystemExit(_main(sys.argv))
