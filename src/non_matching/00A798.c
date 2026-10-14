/* STATUS (Session 5, step 2): NON_MATCHING - best attempt [cc=296] is not byte-exact.
 * 4 bytes short: epilogue order.
 * See docs/progress.md for the family classification. */
/* func_0010A798 @ 0x0010A798 (0x2C bytes): func_0010A740();
 * func_00107020(D_0013231C); return 0. */
int func_0010A740(void);
int func_00107020(int x);

extern int D_0013231C;

int func_0010A798(void) {
    func_0010A740();
    func_00107020(D_0013231C);
    return 0;
}
