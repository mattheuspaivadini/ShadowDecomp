/* GAMECORE.XFF @ 0x12A978 (16 B) - setWormIKBoundDynamics
 * Evidence: ops swc1
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void setWormIKBoundDynamics(char *p, float a, float b, float c) {
    F(p, float, 0x1280) = a;
    F(p, float, 0x1284) = b;
    F(p, float, 0x1288) = c;
}
