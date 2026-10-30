/* GAMECORE.XFF @ 0x103750 (16 B) - setRouteAttackBirdCtrlWork
 * Evidence: ops sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void setRouteAttackBirdCtrlWork(char *p) {
    F(p, int, 0x30) = 1;
    F(p, int, 0x154) = 1;
}
