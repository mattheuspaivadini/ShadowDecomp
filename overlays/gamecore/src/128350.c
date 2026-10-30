/* GAMECORE.XFF @ 0x128350 (16 B) - initTailIKWork
 * Evidence: ops sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void initTailIKWork(int a, int b, char *w) {
    F(w, int, 0x3C0) = 0;
    F(w, int, 0x3C8) = 0;
    F(w, int, 0x3C4) = 0;
}
