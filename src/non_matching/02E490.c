/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 2 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/02E490.s); this C
 * draft (Session 9) is kept for the record. */
extern char D_00139B48[];   /* absolute lui/addiu */
extern char D_00139B38[];   /* absolute lui/addiu */

int func_00128E6C(int a0, int a1);

int func_0012E490(int *a0, int a1, int a2) {
    if (a2 != 0) {
        if (func_00128E6C(a2, (int)D_00139B48) != 0) {
            if (func_00128E6C(a2, (int)D_00139B38) != 0)
                return 0;
        }
        a0[0x34 / 4] = a2;
        a0[0x30 / 4] = a1;
    }
    return (int)D_00139B48;
}
