/* STATUS (Session 5, step 2): NON_MATCHING - best attempt [cc=296] is not byte-exact.
 * 4 bytes short: lw of the result vs epilogue.
 * See docs/progress.md for the family classification. */
/* func_0010FC90 @ 0x0010FC90 (0x34 bytes): read word idx of the table
 * held in D_00132988 through func_0010FBF8. */
int func_0010FBF8(int *dst, int *src, int n);

extern int D_00132988;

int func_0010FC90(int idx) {
    int buf;

    func_0010FBF8(&buf, (int *)(D_00132988 + idx * 4), 4);
    return buf;
}
