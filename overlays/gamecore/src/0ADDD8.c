/* GAMECORE.XFF @ 0x0ADDD8 (12 B) - Kite_ResetEventFrameCheck
 * Evidence: ops sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void Kite_ResetEventFrameCheck(char *p) {
    F(p, int, 8) = 0;
    F(p, int, 0xC) = 0;
}
