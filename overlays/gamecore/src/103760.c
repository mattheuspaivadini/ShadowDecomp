/* GAMECORE.XFF @ 0x103760 (12 B) - resetRouteAttackBirdCtrlWork
 * Evidence: ops sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void resetRouteAttackBirdCtrlWork(char *p) {
    F(p, int, 0x30) = 0;
    F(p, int, 0x154) = 0;
}
