/* GAMECORE.XFF @ 0x019758 (20 B) - gStatGObjDispOff
 * Evidence: and ~1 on [a0+0x10]
 * UNCONFIRMED: none
 */
void gStatGObjDispOff(unsigned int *p) {
    p[4] &= ~1;
}
