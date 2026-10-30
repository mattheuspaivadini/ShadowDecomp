/* GAMECORE.XFF @ 0x0F81B8 (12 B) - setPassageRangeData
 * Evidence: ops swc1
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void setPassageRangeData(char *p, float a, float b) {
    F(p, float, 0x3CC) = a;
    F(p, float, 0x3D0) = b;
}
