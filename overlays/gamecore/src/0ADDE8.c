/* GAMECORE.XFF @ 0x0ADDE8 (20 B) - Kite_StartEventCheck
 * Evidence: ops sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void Kite_StartEventCheck(char *p, int a) {
    F(p, int, 0) = a;
    F(p, int, 8) = 1;
    F(p, int, 4) = 0;
}
