/* STATUS (Session 4, 2026-10-14): NON_MATCHING. same scheduling case as func_00111F90.
 * The original .s stays in the build (asm/cod/0120D0.s); this C
 * attempt is kept for the record. */
/* asm/cod/0120D0.s -> func_001120D0 @ 0x001120D0 (0x28 bytes)
 * Identical to func_00111F90: writes 5 through the getter's pointer, returns -1.
 */
extern int *func_00127528();

int func_001120D0(void) {
    int *p = func_00127528();

    *p = 5;
    return -1;
}
