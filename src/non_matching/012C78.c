/* STATUS (Session 4, 2026-10-14): NON_MATCHING. negative-index branch; the masked-index/constant registers differ (v0/a1 in the original vs a2/v1 in ours).
 * The original .s stays in the build (asm/cod/012C78.s); this C
 * attempt is kept for the record. */
/* asm/cod/012C78.s -> func_00112C78 @ 0x00112C78 (0x4C bytes)
 * Clear the first word of the `index`-th 0xC-byte record of one of two tables.
 * A negative index has its sign bit masked and selects D_0014B364; a
 * non-negative one selects D_0014B36C. Both globals hold a pointer. The store
 * is duplicated per branch in the original (two separate return paths).
 */
extern char *D_0014B364[];
extern char *D_0014B36C[];

void func_00112C78(int index) {
    if (index < 0) {
        index &= 0x7FFFFFFF;
        *(int *)(D_0014B364[0] + index * 0xC) = 0;
    } else {
        *(int *)(D_0014B36C[0] + index * 0xC) = 0;
    }
}
