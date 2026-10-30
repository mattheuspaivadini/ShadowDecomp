/* GAMECORE.XFF @ 0x0ADDA0 (28 B) - Kite_SetEventIDList
 * Evidence: ops sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void Kite_SetEventIDList(char *p, int id, unsigned idx) {
    if (idx < 10)
        F(p, int, 0x1BC + idx * 4) = id;
}
