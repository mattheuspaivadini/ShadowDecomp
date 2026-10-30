/* GAMECORE.XFF @ 0x0FBB68 (12 B) - setUserPathGroupID
 * Evidence: ops sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void setUserPathGroupID(char *p, int a, int b) {
    F(p, int, 0x3C68) = a;
    F(p, int, 0x3C6C) = b;
}
