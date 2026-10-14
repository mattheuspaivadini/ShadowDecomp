/* STATUS (Session 5, step 2): NON_MATCHING - best attempt [cc=296] is not byte-exact.
 * 2 instructions short: the 64-bit sign-extend tail.
 * See docs/progress.md for the family classification. */
/* func_00127500 @ 0x00127500 (0x28 bytes): sign-extend the int returned by
 * func_00129800(a0, 0, 10) to 64 bits. */
int func_00129800(int a0, int a1, int a2);

long long func_00127500(int a0) {
    return func_00129800(a0, 0, 10);
}
