/* STATUS (Session 5, step 2): NON_MATCHING - best attempt [cc=29] is not byte-exact.
 * 4 bytes short: `bgtz` layout of the error return.
 * See docs/progress.md for the family classification. */
/* func_0011A5C8 @ 0x0011A5C8 (0x38 bytes): if (a0 > 0)
 * func_00106E70(D_00151E20, a0), return 0; else 0x81010016. */
int ChangeThreadPriority(int a, int b);

extern int D_00151E20;

int sceMc2ChangeThreadPriority(int a0) {
    if (a0 > 0) {
        ChangeThreadPriority(D_00151E20, a0);
        return 0;
    }
    return 0x81010016;
}
