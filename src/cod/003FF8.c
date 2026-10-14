/* asm/cod/003FF8.s -> func_00103FF8 @ 0x00103FF8
 * Variadic entry point that only saves the argument registers (the EE-GCC
 * `void f(int a0, ...) {}` prologue: 0x60 frame, $f19..$f12 and
 * $a1..$a7 spilled, no body). Evidence: the shape is reproduced
 * byte-for-byte by a plain variadic function with 1 fixed argument(s)
 * (probe: build/tmp/probe_va.c). */
void func_00103FF8(int a0, ...) {
}
