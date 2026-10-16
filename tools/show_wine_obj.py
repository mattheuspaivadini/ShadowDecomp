import sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
import tools.eegcc as e
import subprocess

stem = sys.argv[1] if len(sys.argv) > 1 else "00F4C0"
cc = sys.argv[2] if len(sys.argv) > 2 else "wine:ee-gcc2.95.3-136"
flags = sys.argv[3].split() if len(sys.argv) > 3 else []

import shutil
import tools.matchcheck as mc
import tools.permute as P
import struct

staged = e.WORK / f"build/s8/drafts/{stem}.c"
staged.parent.mkdir(parents=True, exist_ok=True)
shutil.copy2(f"build/s8/drafts/{stem}.c", staged)

obj = Path(f"/tmp/{stem}.o")
err = e.compile_c(f"build/s8/drafts/{stem}.c", obj, extra=flags, compiler=cc, stage=False)
print("compile err:", err)
if not err and obj.exists():
    info = mc.parse_asm(stem)
    words, masks = P.load_variant_words(obj, info["symbol"])
    rom = mc.ROM.read_bytes()
    rom_off = info["addr"] - mc.ROM_BASE
    orig = rom[rom_off:rom_off + info["size"]]
    while len(orig) >= 4 and orig[-4:] == b"\x00\x00\x00\x00":
        orig = orig[:-4]
    owords = list(struct.unpack(f"<{len(orig) // 4}I", orig))
    score, back = P.edit_distance(owords, words, masks)
    print(f"SCORE: {score}")
    subprocess.run(["mips-linux-gnu-objdump", "-dr", str(obj)])

