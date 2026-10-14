/* STATUS (Session 5, step 2): NON_MATCHING - best attempt [cc=296/-fno-optimize-sibling-calls] is not byte-exact.
 * 4 bytes short: `move a0,v0` placed in the first jal delay slot.
 * See docs/progress.md for the family classification. */
/* func_00130AF0 @ 0x00130AF0 (0x28 bytes): func_001258A0(func_00130AC8()). */
int func_00130AC8(void);
int func_001258A0(int x);

int func_00130AF0(void) {
    int v = func_00130AC8();

    return func_001258A0(v);
}
