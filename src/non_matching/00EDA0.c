/* STATUS (Session 5, step 2): NON_MATCHING - best attempt [cc=296/-fno-optimize-sibling-calls] is not byte-exact.
 * 4 instructions: argument copy `a2=a1` is scheduled after the callback `lui`; original moves it first (right-to-left argument evaluation).
 * See docs/progress.md for the family classification. */
/* func_0010EDA0 @ 0x0010EDA0 (0x28 bytes): forwards (a0, &D_00138198,
 * a1, 1) to func_0010EC78. Second argument moves before its register is
 * reused. */
int func_0010EC78(int a, const char *b, int c, int d);

extern char D_00138198[];

void func_0010EDA0(int a, int b) {
    func_0010EC78(a, D_00138198, b, 1);
}
