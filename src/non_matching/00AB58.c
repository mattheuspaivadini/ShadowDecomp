/* STATUS (Session 5, step 2): NON_MATCHING - best attempt [cc=296] is not byte-exact.
 * 4 bytes short: epilogue shape after the call.
 * See docs/progress.md for the family classification. */
/* func_0010AB58 @ 0x0010AB58 (0x34 bytes): D_00132314 = 0, then
 * func_001283D0(D_001470E8, 0, 4); return 0. */
int func_001283D0(void *dst, int val, int size);

extern int D_00132314;
extern char D_001470E8[];

int func_0010AB58(void) {
    D_00132314 = 0;
    func_001283D0(D_001470E8, 0, 4);
    return 0;
}
