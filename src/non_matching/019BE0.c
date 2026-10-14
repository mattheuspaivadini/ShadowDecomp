/* STATUS (Session 5, step 2): NON_MATCHING - best attempt [cc=296/-fno-optimize-sibling-calls] is not byte-exact.
 * constant order (a3/a4/a5).
 * See docs/progress.md for the family classification. */
/* func_00119BE0 @ 0x00119BE0 (0x24 bytes): forwards through with
 * a3=0x800, a4=0x200, a5=0x20 to func_00119C08. */
int func_00119C08(int a, int b, int c, int d, int e, int f);

void func_00119BE0(int a, int b, int c) {
    func_00119C08(a, b, c, 0x800, 0x200, 0x20);
}
