/* STATUS (Session 34, 2026-10-19): NON_MATCHING. best score 35 [cc=29].
 * wildcard matcher (? and *), recursion through func_0011BAE8/strncmp/strcmp. min(q,s) ternary fixed
 * the movz. Residual = which of the three identical 'return 1' blocks survives cross-jumping (ours
 * keeps the one in the ? loop, the original keeps the one after the recursive call).
 * Tried: four ? loop shapes, four recursion loop shapes, shared goto label inside the recursive
 * branch, continue instead of if-*, if/else on *str, cc=296 (78).
 * The original .s stays in the build (asm/cod/01BCC8.s); this C
 * draft (Session 34) is kept for the record. */
int func_0011BAE8(const char *s, char c);
int func_00128E6C(const char *a, const char *b);
int func_00129200(const char *a, const char *b, int n);

int func_0011BCC8(const char *str, const char *pat) {
    int q, s, n;

    while (q = func_0011BAE8(pat, '?'), s = func_0011BAE8(pat, '*'), q >= 0 || s >= 0) {
        n = s;
        if (q >= 0) {
            n = q;
            if (s >= 0) n = q < s ? q : s;
        }
        if (func_00129200(pat, str, n) != 0) return 0;
        pat += n;
        str += n;
        while (*pat == '?') {
            pat++;
            if (*str == '\0') return 1;
            str++;
        }
        if (*pat == '*') {
            while (*++pat == '*' || *pat == '?')
                ;
            if (*pat == '\0') return 1;
            while ((n = func_0011BAE8(str, *pat)) >= 0) {
                str += n;
                if (func_0011BCC8(str, pat) == 1) return 1;
                str++;
            }
            return 0;
        }
    }
    return func_00128E6C(pat, str) == 0;
}
