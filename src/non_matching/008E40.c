/* STATUS (10, 2026-10-16): NON_MATCHING. best score 7 [cc=29].
 * 
 * The original .s stays in the build (asm/cod/008E40.s); this C
 * draft (10) is kept for the record. */
/* asm/cod/008E40.s -> func_00108E40 @ 0x00108E40 (0x48 bytes, 18 insns)
 * Variadic shim with a FIXED callback: a0 is copied into the one-word stack
 * buffer at sp+0x0, the incoming vararg registers are spilled by the EE-GCC
 * varargs prologue (a3..a7 -> 0x68/0x70/0x78/0x80/0x88 = 5 slots, i.e. 3 fixed
 * arguments), and func_00107FF8(cb=func_00108D10, p=&buf, a1, a2, ap=sp+0x68)
 * is called; its value is returned through an intermediate local (hence the
 * `jal` + real epilogue instead of a tail `j`).
 * The va_list value is the register save area; the SDK's stdarg.h spells this
 * as `va_start`, which this compiler implements with __builtin_saveregs()
 * (the toolchain here ships no stdarg.h, so the builtin is used directly).
 * MATCH GUESS: cc=29 (0x008D6x/008D9x/009198 family) */
extern int func_00108D10(void);
extern int func_00107FF8(int (*cb)(), int *p, int a1, int a2, int ap);

int sceSnprintf(int a0, int a1, int a2, ...) {
    int buf;
    int r;

    buf = a0;
    r = func_00107FF8(func_00108D10, &buf, a1, a2, (int)__builtin_saveregs());
    return r;
}
