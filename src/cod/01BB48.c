/* asm/cod/01BB48.s -> func_0011BB48.
 * basename length < 0x20 check; >= returns (Session 23)
 * MATCHED. */
char *func_00128CDC(const char *s, int c);
char *func_00129578(const char *s, int c);
unsigned int func_001290C4(const char *s);
int func_0011BB48(const char *s) {
    if (func_00128CDC(s, 0x2F) != 0) {
        if (func_001290C4(func_00129578(s, 0x2F) + 1) >= 0x20) return 0;
    } else {
        if (func_001290C4(s) >= 0x20) return 0;
    }
    return 1;
}
