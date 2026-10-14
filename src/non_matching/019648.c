/* STATUS (Session 5, step 2): NON_MATCHING - best attempt [cc=296/-fno-optimize-sibling-calls] is not byte-exact.
 * 3 instructions: constant materialisation order (a5=0x10 hoisted before sd ra).
 * See docs/progress.md for the family classification. */
/* func_00119648 @ 0x00119648 (0x24 bytes): forwards through with a3=9,
 * a4=original a3, a5=0x10 to func_00118E58. */
int func_00118E58(int a, int b, int c, int d, int e, int f);

void func_00119648(int a, int b, int c, int d) {
    func_00118E58(a, b, c, 9, d, 0x10);
}
