/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 2 [cc=29].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/00AAC8.s); this C
 * draft (Session 9) is kept for the record. */
extern char D_0013227C[];   /* 4-byte id word, absolute lui/addiu */
extern char D_001470E8[];   /* 4-byte id word, absolute lui/addiu */
extern int  D_00132328[];   /* 4-byte runtime word, reloaded via $s0 */

int func_00128188(unsigned int a0, unsigned int a1, unsigned int n);

int func_0010AAC8(void) {
    int r = 0;

    if (func_00128188((unsigned int)D_001470E8, (unsigned int)D_0013227C, 4)
        != 0) {
        if (func_00128188((unsigned int)D_001470E8,
                          (unsigned int)D_00132328[0], 4) != 0) {
            r = func_00128188((unsigned int)D_0013227C,
                              (unsigned int)D_00132328[0], 4) != 0;
        }
    }
    return r;
}
