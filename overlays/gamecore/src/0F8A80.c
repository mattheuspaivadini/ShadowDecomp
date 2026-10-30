/* GAMECORE.XFF @ 0x0F8A80 (12 B) - setPathRayWideParam
 * Evidence: ops sw swc1
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void setPathRayWideParam(char *p, float w, int n) {
    F(p, float, 0x3C3C) = w;
    F(p, int, 0x3C40) = n;
}
