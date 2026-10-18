/* asm/cod/001AA0.s -> func_00101AA0.
 * DecodeSection error callback: LoaderSysJumpRecoverPoint(fmt, $ra - 8) with $ra read through a local register variable (__builtin_return_address(0) loads through $ra in ee-gcc 2.96) (Session 28).
 * MATCHED. */
extern char D_001363A8[];

void LoaderSysJumpRecoverPoint(const char *fmt, ...);

void func_00101AA0(void) {
    register char *ra asm("$31");

    LoaderSysJumpRecoverPoint(D_001363A8, ra - 8);
}
