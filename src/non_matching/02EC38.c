/* STATUS (Session 5, step 2): NON_MATCHING - best attempt [cc=296] is not byte-exact.
 * 4 bytes short: store/epilogue order.
 * See docs/progress.md for the family classification. */
/* func_0012EC38 @ 0x0012EC38 (0x38 bytes): func_0012E7E8(a0, 1), then
 * store a1 at 0x14 and 1 at 0x10. */
char *func_0012E7E8(int a0, int a1);

void func_0012EC38(int a0, int a1) {
    int *p = (int *)func_0012E7E8(a0, 1);

    p[5] = a1;
    p[4] = 1;
}
