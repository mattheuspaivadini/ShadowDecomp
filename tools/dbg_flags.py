#!/usr/bin/env python3
import sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
import build, eegcc

for stem in ("014C30", "004E78", "001A48"):
    print(stem, "src=", build.load_c_sources().get(stem), "flags=", build.load_c_flags(stem))
print("cflags:", eegcc.cflags())
