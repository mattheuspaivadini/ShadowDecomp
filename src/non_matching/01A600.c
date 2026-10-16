/* STATUS (Session 5, step 2): NON_MATCHING - best attempt [cc=29] is not byte-exact.
 * 4 bytes short: same as 01A5C8.
 * See docs/progress.md for the family classification. */
/* func_0011A600 @ 0x0011A600 (0x38 bytes): same as 01A5C8 with
 * func_00106E80. */
int iChangeThreadPriority(int a, int b);

extern int D_00151E20;

int sceMc2iChangeThreadPriority(int a0) {
    if (a0 > 0) {
        iChangeThreadPriority(D_00151E20, a0);
        return 0;
    }
    return 0x81010016;
}
