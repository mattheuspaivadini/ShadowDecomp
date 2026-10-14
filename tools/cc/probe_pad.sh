#!/bin/bash
# Probe: does `objcopy --update-section .text=<padded>` grow an object's .text?
set -e
W=/root/shadowdecomp-work
mkdir -p $W/obj/padtest && cd $W/obj/padtest
/mnt/c/Users/Matheus/Documents/ShadowDecomp/tools/cc/eegcc.sh -c -O2 -g2 -G8 -Iinclude $W/src/cod/0128C0.c -o a.o
echo "before:"; mips-linux-gnu-readelf -SW a.o | grep -E '\.text'
mips-linux-gnu-objcopy -O binary --only-section=.text a.o t.bin
ls -l t.bin
printf '\0\0\0\0' >> t.bin
ls -l t.bin
echo "update-section (2-arg form):"
mips-linux-gnu-objcopy --update-section=.text=t.bin a.o b.o && mips-linux-gnu-readelf -SW b.o | grep -E '\.text'
echo "update-section (space form):"
mips-linux-gnu-objcopy --update-section .text=t.bin a.o c.o && mips-linux-gnu-readelf -SW c.o | grep -E '\.text'
echo "objdump b.o:"; mips-linux-gnu-objdump -d b.o | tail -8
