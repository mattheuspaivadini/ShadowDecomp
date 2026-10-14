/* MATCHED (Session 6): byte-exact with the 2.9-ee-991111-01 revision (cc=29) —
 * same scheduling case as func_00111F90, resolved by the revision.
 *
 * asm/cod/0120D0.s -> func_001120D0 @ 0x001120D0 (0x28 bytes)
 * Identical to func_00111F90: writes 5 through the getter's pointer, returns -1.
 */
extern int *func_00127528();

int func_001120D0(void) {
    int *p = func_00127528();

    *p = 5;
    return -1;
}
