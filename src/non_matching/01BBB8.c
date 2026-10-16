/* STATUS (Session 12, 2026-10-16): NON_MATCHING. best score 3 [cc=296].
 * func_0011BBB8: beqzl vs beqz branch-likely on slti result in string validator
 * The original .s stays in the build (asm/cod/01BBB8.s); this C
 * draft (Session 12) is kept for the record. */
int func_0011BBB8(const char *s) {
    while (*s != '\0') {
        int c = (signed char)(unsigned char)*s;
        if (c == '?')
            return 0;
        if (c == '*' || c < 0x20)
            return 0;
        s++;
    }
    return 1;
}
