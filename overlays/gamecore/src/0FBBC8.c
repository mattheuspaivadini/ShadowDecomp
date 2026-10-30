/* GAMECORE.XFF @ 0x0FBBC8 (32 B) - getPPointPasasgeNum
 * Evidence: lw 0x3C60 compared against 9, then lw 0x3CB0
 * UNCONFIRMED: field names/types guessed from offsets
 */
int getPPointPasasgeNum(char *p) {
    if (*(int *)(p + 0x3C60) != 9)
        return 0;
    return *(int *)(p + 0x3CB0);
}
