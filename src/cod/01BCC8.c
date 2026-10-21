/* asm/cod/01BCC8.s -> func_0011BCC8.
 * wildcard matcher (? and *); empty asm on pat in the ? loop picks the cross-jump survivor (Session 42)
 * MATCHED. */
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
            asm("" : "+r"(pat));    /* decides which return-1 block survives cross-jumping */
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
