/* STATUS (10, 2026-10-16): NON_MATCHING. best score 5 [cc=29].
 * 
 * The original .s stays in the build (asm/cod/008DB8.s); this C
 * draft (10) is kept for the record. */
/* asm/cod/008DB8.s -> func_00108DB8 @ 0x00108DB8 (0x4C bytes, 19 insns)
 * Variadic shim forwarding the caller's callback: the incoming vararg
 * registers are spilled by the EE-GCC varargs prologue (a4..a7 ->
 * 0x60/0x68/0x70/0x78 = 4 slots, i.e. 4 fixed arguments); then
 * func_00107FF8(cb, a1, *a2, a3, ap=sp+0x60) is called, the count at *a2 is
 * decremented by the result (the reload after the call is the trailing
 * `lw $v1,0x0($s0)`) and the result is returned.
 * The va_list value is the register save area; the SDK's stdarg.h spells this
 * as `va_start`, which this compiler implements with __builtin_saveregs()
 * (the toolchain here ships no stdarg.h, so the builtin is used directly).
 * MATCH GUESS: cc=29 (0x008D6x/008D9x/009198 family) */
extern int func_00107FF8(int (*cb)(), int a1, int a2, int a3, int ap);

int func_00108DB8(int (*cb)(), int a1, int *a2, int a3, ...) {
    int r;

    r = func_00107FF8(cb, a1, *a2, a3, (int)__builtin_saveregs());
    *a2 = *a2 - r;
    return r;
}
