/* STATUS (Session 5, step 2): NON_MATCHING - best attempt [cc=296] is not byte-exact.
 * 1 instruction short (40 vs 36 B): the return-value chain `and`+`sltu` differs.
 * See docs/progress.md for the family classification. */
/* func_0010F0F0 @ 0x0010F0F0 (0x28 bytes): func_001073F0(4) & 0x10000. */
int func_001073F0(int x);

int func_0010F0F0(void) {
    int r = func_001073F0(4);

    return (r & 0x10000) != 0;
}
