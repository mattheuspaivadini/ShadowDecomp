/* asm/cod/005948.s -> func_00105948 @ 0x00105948
 * Variadic entry point that only saves the argument registers (the EE-GCC
 * `void f(int a0, ...) {}` prologue: 0x50 frame, $f19..$f12 and
 * $a2..$a7 spilled, no body). Evidence: the shape is reproduced
 * byte-for-byte by a plain variadic function with 2 fixed argument(s)
 * (probe: build/tmp/probe_va.c). */
void func_00105948(int a0, int a1, ...) {
}
