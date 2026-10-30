/* GAMECORE.XFF @ 0x030BD0 (20 B) - bgmPlay
 * Evidence: swc1 f12 -> +0xC; [+0x24] |= 1
 * UNCONFIRMED: none
 */
void bgmPlay(unsigned int *p, float v) {
    ((float *)p)[3] = v;
    p[9] |= 1;
}
