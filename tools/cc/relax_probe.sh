#!/bin/bash
# Probe whether mips-linux-gnu-ld relaxes an out-of-range %gp_rel reference.
set -e
D=/mnt/c/Users/Matheus/Documents/ShadowDecomp/tools/cc
cd /tmp && rm -rf relax && mkdir relax && cd relax
mips-linux-gnu-as -EL -march=5900 -mabi=eabi -o p.o "$D/relax_probe.s"
mips-linux-gnu-objcopy --set-section-alignment .text=4 p.o
mips-linux-gnu-ld -EL -T "$D/relax_probe.ld" -o p.elf p.o
mips-linux-gnu-objcopy -O binary p.elf p.bin
echo "--- flat bytes ---"
xxd p.bin
echo "--- linked disassembly ---"
mips-linux-gnu-objdump -d p.elf | tail -8
