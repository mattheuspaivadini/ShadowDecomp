/* GAMECORE.XFF @ 0x0F8A68 (24 B) - setSearchPointMax
 * Evidence: ops sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void setSearchPointMax(char *p, int n) {
    if (n <= 0)
        F(p, int, 0x3BC) = 0x380;
    else
        F(p, int, 0x3BC) = n;
}
