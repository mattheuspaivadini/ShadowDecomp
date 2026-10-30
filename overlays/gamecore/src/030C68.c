/* GAMECORE.XFF @ 0x030C68 (24 B) - bgmChangeVol
 * Evidence: f12 -> +0x10, f13 -> +0x14; [+0x24] |= 2
 * UNCONFIRMED: none
 */
void bgmChangeVol(unsigned int *p, float a, float b) {
    ((float *)p)[5] = b;
    ((float *)p)[4] = a;
    p[9] |= 2;
}
