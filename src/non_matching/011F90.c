/* STATUS (Session 4, 2026-10-14): NON_MATCHING. scheduling: the original materialises the constant before the epilogue `ld ra`; ours loads ra first.
 * The original .s stays in the build (asm/cod/011F90.s); this C
 * attempt is kept for the record. */
/* asm/cod/011F90.s -> func_00111F90 @ 0x00111F90 (0x28 bytes)
 *   addiu sp,sp,-0x10; sd ra,0(sp)
 *   jal func_00127528
 *    nop
 *   addiu v1,zero,0x5
 *   ld ra,0(sp)
 *   sw v1,0x0(v0)              ; *func_00127528() = 5
 *   addiu v0,zero,-0x1
 *   jr ra; addiu sp,sp,0x10
 * Writes 5 through the pointer returned by the getter and returns -1.
 */
extern int *func_00127528();

int func_00111F90(void) {
    int *p = func_00127528();

    *p = 5;
    return -1;
}
