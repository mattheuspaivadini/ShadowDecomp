/* STATUS (Session 5, step 2): NON_MATCHING - best attempt [cc=296] is not byte-exact.
 * 22 instructions: descending word compare + movz.
 * See docs/progress.md for the family classification. */
/* func_0012F0D8 @ 0x0012F0D8 (0x68 bytes): record compare: sizes at 0x10,
 * then word-by-word compare from the end; 1 if a < b, -1 if a > b. */
int __mcmp(int *a, int *b) {
    int n = a[4];
    int i;

    if (n != b[4])
        return n - b[4];
    for (i = n - 1; i >= 0; i--) {
        if (a[5 + i] != b[5 + i])
            return (unsigned)a[5 + i] < (unsigned)b[5 + i] ? 1 : -1;
    }
    return 0;
}
