/* STATUS (Session 5, step 2): NON_MATCHING - best attempt [cc=296] is not byte-exact.
 * 4 bytes short: epilogue shape after the call.
 * See docs/progress.md for the family classification. */
/* func_0010E3C8 @ 0x0010E3C8 (0x38 bytes): D_00132330 = -1, then
 * func_001283D0(D_001475A8, 0, 4); return 0. */
int func_001283D0(void *dst, int val, int size);

extern int D_00132330;
extern char D_001475A8[];

int func_0010E3C8(void) {
    D_00132330 = -1;
    func_001283D0(D_001475A8, 0, 4);
    return 0;
}
