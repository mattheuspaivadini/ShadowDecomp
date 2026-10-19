/* asm/cod/01BE48.s -> func_0011BE48.
 * strtok-like tokenizer with "quoted" tokens (strcpy into D_0015DE48 first; .bss save pointer)
 * MATCHED. */
extern char D_00138D00[];
extern char *D_0015DE40 __attribute__((section(".bss")));
extern char D_0015DE48[];

char *func_00128CDC(const char *s, int c);
void func_00128FB0(char *dst, const char *src);

char *func_0011BE48(char *str, const char *delim) {
    char *tok;

    if (str != 0) {
        func_00128FB0(D_0015DE48, str);
        str = D_0015DE48;
    }
    if (str == 0) {
        str = D_0015DE40;
        if (str == 0) {
            return 0;
        }
    }
    if (*str == '\0') {
        return 0;
    }
    while (func_00128CDC(delim, (char)*str++) != 0) {
        if (*(str - 1) == '\0') {
            return 0;
        }
    }
    tok = str - 1;
    if (*(str - 1) == '"') {
        tok = str;
        while (func_00128CDC(D_00138D00, *str++) == 0)
            ;
    } else {
        while (func_00128CDC(delim, *str++) == 0)
            ;
    }
    if (*(str - 1) != 0) {
        D_0015DE40 = str;
    } else {
        D_0015DE40 = 0;
    }
    *(str - 1) = '\0';
    return tok;
}
