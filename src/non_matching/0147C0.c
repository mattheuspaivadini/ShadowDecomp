/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 12 [cc=29].
 * R1 wave3d: 0x00FFFFFF as lui+addiu with the lui hoisted
 * The original .s stays in the build (asm/cod/0147C0.s); this C
 * draft (Session 8) is kept for the record. */
int func_00108EF8(const char *msg);
int func_00114F58(int *p);

extern char D_001384F0[];   /* lui/%lo: non-small */

void func_001147C0(int *p) {
    int i;

    i = 0xFFFFFF;
    while ((*p & 0x100) != 0) {
        if (i < 0) {
            func_00108EF8(D_001384F0);
            func_00114F58(p);
        }
        i--;
    }
}
