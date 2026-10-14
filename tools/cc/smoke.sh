#!/bin/bash
# Minimal ee-gcc2.96 smoke test: compile trivial C, disassemble the .o.
set -e
EE=/usr/local/sce/ee/gcc
mkdir -p /tmp/eetest && cd /tmp/eetest
printf 'int add(int a,int b){return a+b;}\nint gl(void){return add(1,2);}\n' > t.c
"$EE/bin/ee-gcc" -c -O2 t.c -o t.o
mips-linux-gnu-objdump -d t.o
