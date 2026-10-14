#!/usr/bin/env python3
"""Print the flags/hash that the build derives from config/compiler_flags.mk."""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import eegcc

print("cflags  :", eegcc.cflags())
print("asflags :", eegcc.flag("EE_ASFLAGS"))
print("ld      :", eegcc.flag("EE_LD"))
print("sha1    :", eegcc.flag("ROM_SHA1"))
print("size    :", eegcc.flag("ROM_SIZE"))
print("work    :", eegcc.WORK)
