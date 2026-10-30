/* GAMECORE.XFF @ 0x12AC38 (28 B) - getEventScriptClass
 * Evidence: lbu 8(a0) compared with 0x20 held in a0, movn selects a0+0x20 or 0
 * UNCONFIRMED: register pin of constant 0x20 in $a0 + empty asm reproduces the compare shape (compiler artifact); type of struct unknown
 */
char *getEventScriptClass(char *p) {
    char *q = p;
    register int k asm("$4") = 0x20;
    asm("" : "+r"(k));
    return *(unsigned char *)(q + 8) == k ? q + 0x20 : 0;
}
