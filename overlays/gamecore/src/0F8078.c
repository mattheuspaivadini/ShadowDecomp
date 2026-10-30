/* GAMECORE.XFF @ 0x0F8078 (12 B) - setSelfColAndNearMinDist
 * Evidence: ops sw swc1
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void setSelfColAndNearMinDist(char *p, float d, int c) {
    F(p, float, 0x3C0) = d;
    F(p, int, 0x3C4) = c;
}
