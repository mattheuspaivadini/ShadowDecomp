/* GAMECORE.XFF @ 0x0ADE00 (16 B) - Kite_EndEventCheck
 * Evidence: ops sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void Kite_EndEventCheck(char *p) {
    F(p, int, 4) = 1;
    F(p, int, 0xC) = 1;
}
