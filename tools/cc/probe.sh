#!/bin/bash
# Probe how the ee-gcc2.96 driver locates cc1/cpp0/as under this prefix.
T=/mnt/c/Users/Matheus/Documents/ShadowDecomp/tools/cc/ee-gcc2.96
GV=2.96-ee-001003-1
GCC=/usr/local/sce/ee/gcc/bin/ee-gcc
mkdir -p /tmp/eetest && cd /tmp/eetest
printf 'int add(int a,int b){return a+b;}\n' > t.c

try() {
  local label="$1"; shift
  rm -f t.o
  if "$@" >/tmp/eetest/log 2>&1; then
    echo "OK   $label -> $(mips-linux-gnu-size t.o 2>/dev/null | tail -1)"
  else
    echo "FAIL $label :: $(head -1 /tmp/eetest/log)"
  fi
}

try "plain"                 "$GCC" -c -O2 t.c -o t.o
try "B-gccdir+B-asdir"      "$GCC" -B"$T/lib/gcc-lib/ee/$GV/" -B"$T/ee/bin/" -c -O2 t.c -o t.o
try "GCC_EXEC_PREFIX=lib/gcc-lib/" env GCC_EXEC_PREFIX="$T/lib/gcc-lib/" "$GCC" -c -O2 t.c -o t.o
try "GCC_EXEC_PREFIX=lib/gcc-lib/ee/V" env GCC_EXEC_PREFIX="$T/lib/gcc-lib/ee/$GV/" "$GCC" -c -O2 t.c -o t.o
try "GCC_EXEC_PREFIX=prefix-prefix" env GCC_EXEC_PREFIX="/usr/local/sce/ee/gcc/lib/gcc-lib/" "$GCC" -c -O2 t.c -o t.o
try "B+EXEC_PREFIX"         env GCC_EXEC_PREFIX="$T/lib/gcc-lib/" "$GCC" -B"$T/lib/gcc-lib/ee/$GV/" -B"$T/ee/bin/" -c -O2 t.c -o t.o
try "PATH+cc1sym"           env PATH="$T/lib/gcc-lib/ee/$GV:$T/ee/bin:$PATH" "$GCC" -c -O2 t.c -o t.o
