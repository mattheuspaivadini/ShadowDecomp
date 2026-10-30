/* GAMECORE.XFF @ 0x0ADDC0 (24 B) - Kite_InitEventCheck
 * Evidence: ops sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void Kite_InitEventCheck(char *p) {
    F(p, int, 4) = 0;
    F(p, int, 8) = 0;
    F(p, int, 0) = -1;
    F(p, int, 0xC) = 0;
}
