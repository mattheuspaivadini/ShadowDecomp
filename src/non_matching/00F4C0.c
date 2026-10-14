/* STATUS (Session 5, step 2): NON_MATCHING - best attempt [cc=296] is not byte-exact.
 * 9 instructions: branch layout of the range check.
 * See docs/progress.md for the family classification. */
/* func_0010F4C0 @ 0x0010F4C0 (0x30 bytes): range check (a0-13 < 0x23
 * unsigned) then func_0010F4B0(), else -1. */
int func_0010F4B0(void);

int func_0010F4C0(int a0) {
    int r = a0 - 0xD;

    if ((unsigned)r < 0x23)
        return func_0010F4B0();
    return -1;
}
