/* STATUS (Session 5, step 2): NON_MATCHING - best attempt [cc=296/-fno-optimize-sibling-calls] is not byte-exact.
 * same as 01B718.
 * See docs/progress.md for the family classification. */
/* func_0011B740 @ 0x0011B740 (0x24 bytes): forwards (0, a0, a1) to
 * func_0011B670. */
int func_0011B670(int a, int b, int c);

void func_0011B740(int a, int b) {
    func_0011B670(0, a, b);
}
