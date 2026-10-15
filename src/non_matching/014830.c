/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 13 [cc=29].
 * R4 w25a_2: clean guess but not byte-exact
 * The original .s stays in the build (asm/cod/014830.s); this C
 * draft (Session 8) is kept for the record. */
extern char D_001384F0[];   /* lui/%lo -> non-small */

int  func_00108EF8(const char *msg);
void func_00114F58(void *p);

void func_00114830(int *p, int a1, int a2) {
    int t;

    for (t = (a2 ? a2 : 0x1000000) - 1; (unsigned int)p[4] < (unsigned int)a1; t--) {
        if (t < 0) {
            func_00108EF8(D_001384F0);
            func_00114F58(p);
        }
    }
}
