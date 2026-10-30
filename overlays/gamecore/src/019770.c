/* GAMECORE.XFF @ 0x019770 (12 B) - gStatGObjDispChk
 * Evidence: andi 1 on [a0+0x10]
 * UNCONFIRMED: none
 */
int gStatGObjDispChk(unsigned int *p) {
    return p[4] & 1;
}
