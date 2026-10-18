/* asm/cod/01BAE8.s -> func_0011BAE8.
 * strchr-index helper; while (*p && *p != c) (Session 23)
 * MATCHED. */
int func_0011BAE8(const char *s, char c) {
    const char *p = s;
    while (*p && *p != c) p++;
    if (*p == c) return p - s;
    return -1;
}
