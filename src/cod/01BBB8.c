/* asm/cod/01BBB8.s -> func_0011BBB8.
 * SCE libmc name check; single || condition (Session 19)
 * MATCHED. */
int func_0011BBB8(const char *s) {
    while (*s != '\0') {
        int c = (signed char)(unsigned char)*s;
        if (c == '?' || c == '*' || c < 0x20)
            return 0;
        s++;
    }
    return 1;
}
