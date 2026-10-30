/* GAMECORE.XFF @ 0x0F88D8 (28 B) - getWayFinish
 * Evidence: ops lw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
int getWayFinish(char *p) {
    int r = 0;
    if (F(p, int, 0x408))
        r = F(p, int, 0x380) == 0;
    return r;
}
