/* GAMECORE.XFF @ 0x0ADE50 (12 B) - Kite_SetKiteObj
 * Evidence: ops sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void Kite_SetKiteObj(char *p, int o) {
    F(p, int, 0xF0) = o;
    F(p, int, 0x1E8) = o;
}
