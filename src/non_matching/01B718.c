/* STATUS (Session 5, step 2): NON_MATCHING - best attempt [cc=296/-fno-optimize-sibling-calls] is not byte-exact.
 * 9 instructions: argument shift with an extra copy through v0.
 * See docs/progress.md for the family classification. */
/* func_0011B718 @ 0x0011B718 (0x24 bytes): forwards (1, a0, a1) to
 * func_0011B670. */
int func_0011B670(int a, int b, int c);

void func_0011B718(int a, int b) {
    func_0011B670(1, a, b);
}
