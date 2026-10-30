/* GAMECORE.XFF @ 0x0F8968 (36 B) - useTempAttain
 * Evidence: loads $v0, 0x3A0($a0), $v1, 0x410($a0)
 
 */
/* UNCONFIRMED: +0x3A0 blocks the temporary attain, +0x410 is its enable flag. */
int useTempAttain(char *p) {
    if (*(int *)(p + 0x3A0) == 0 && *(int *)(p + 0x410) != 0)
        return 1;
    return 0;
}
