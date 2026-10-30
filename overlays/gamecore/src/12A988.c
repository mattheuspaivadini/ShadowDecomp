/* GAMECORE.XFF @ 0x12A988 (44 B) - setWormIKNodeLimit
 * Evidence: stores $f12, 0x0($a0)
 
 */
void setWormIKNodeLimit(char *p, float v) {
    int i = 0x1F;
    char *q = p + 0x9F0;
    do {
        i--;
        *(float *)q = v;
        q -= 0x50;
    } while (i >= 0);
}
