/* asm/cod/01BC10.s -> func_0011BC10.
 * SCE libmc file-name check (rejects . and ..) (Session 19)
 * MATCHED. */
extern char D_00138CF0[];
extern char D_00138CF8[];

char *func_00128CDC(char *s, int c);        /* strchr */
char *func_00129578(const char *s, int c);  /* strrchr */
unsigned int func_001290C4(char *s);        /* strlen */
void func_00128FB0(char *dst, char *src);   /* strcpy */
int func_00128E6C(char *a, char *b);        /* strcmp */

int func_0011BC10(char *a0) {
    char buf[0x20];

    if (func_00128CDC(a0, 0x2F) != 0) {
        if (func_001290C4(func_00129578(a0, 0x2F) + 1) >= 0x20)
            return 0;
        func_00128FB0(buf, func_00129578(a0, 0x2F) + 1);
    } else {
        if (func_001290C4(a0) >= 0x20)
            return 0;
        func_00128FB0(buf, a0);
    }
    if (func_00128E6C(buf, D_00138CF0) == 0)
        return 0;
    if (func_00128E6C(buf, D_00138CF8) != 0)
        return 1;
    /* UNCONFIRMED: the empty asm keeps the 0/1 return as branches (no sltu
     * store-flag); the original spelling is unknown. */
    __asm__ volatile ("");
    return 0;
}
