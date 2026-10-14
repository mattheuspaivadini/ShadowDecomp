# Manifest

`files.txt` lists every regular file extracted from `Shadow of the Colossus (USA).iso`,
with: size (bytes), ISO LBA, SHA-1, MD5, path.

Regenerate:

    python tools/extract_iso.py "Shadow of the Colossus (USA).iso" extracted manifest/files.txt

Source image (never modified, never committed):

| File | Size (bytes) | First bytes |
|------|--------------|-------------|
| `Shadow of the Colossus (USA).iso` | 2,693,955,584 | `05 05 …` (system area), ISO9660 PVD at `0x8000` |

`SYSTEM.CNF` (57 bytes, SHA-1 `70703f0d6eaa36554416add460e4c62b983a946d`):

    BOOT2 = cdrom0:\SCUS_974.72;1
    VER = 1.00
    VMODE = NTSC

Main executable: **`SCUS_974.72`**, 242,940 bytes,
SHA-1 `b715b3496aad6f7601a0ab8495acd1d151a1ff7b`.

Other artifacts in this directory:

- `iso_listing.txt` — full ISO file listing (size, LBA, path).
- `elf_header.json` — parsed ELF header, program headers, sections.
- `strings.txt` — 319 address/string pairs from the ELF.
- `functions_ghidra_raw.txt` — raw Ghidra function inventory (boundaries unreliable, see docs/analysis.md).
