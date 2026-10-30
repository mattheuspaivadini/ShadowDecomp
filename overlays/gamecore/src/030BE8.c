/* GAMECORE.XFF @ 0x030BE8 (32 B) - bgmStop
 * Evidence: f12 -> +0x18; if a1 *a1=0; a1 -> +0x20; [+0x24] |= 4
 * UNCONFIRMED: none
 */
void bgmStop(unsigned int *p, float v, int *q) {
    ((float *)p)[6] = v;
    if (q)
        *q = 0;
    p[8] = (unsigned int)q;
    p[9] |= 4;
}
