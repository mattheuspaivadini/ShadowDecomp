/* STATUS (Session 5, step 2): NON_MATCHING - best attempt [cc=296] is not byte-exact.
 * 4 bytes short: epilogue/constant order.
 * See docs/progress.md for the family classification. */
/* func_00112B98 @ 0x00112B98 (0x34 bytes): func_00107540(5);
 * func_00106D10(5, D_0014B354); D_00133948 = 0. */
int func_00107540(int x);
int func_00106D10(int a, int b);

extern int D_0014B354;
extern int D_00133948 __attribute__((section(".data")));

void func_00112B98(void) {
    func_00107540(5);
    func_00106D10(5, D_0014B354);
    D_00133948 = 0;
}
