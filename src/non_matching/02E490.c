/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 2 [cc=296].
 * strcmp chain, assigns 0x34 then 0x30, returns &D_00139B48; wave4c (R1)
 * The original .s stays in the build (asm/cod/02E490.s); this C
 * draft (Session 8) is kept for the record. */
extern char D_00139B48[];              /* lui/%lo - non-small */
extern char D_00139B38[];              /* lui/%lo - non-small */
extern int func_00128E6C(int a0, int a1);

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
