/* GAMECORE.XFF @ 0x02C930 (32 B) - stagemanager_restartstagecore
 * Evidence: t0=a3, t1=1, a3=-1, sibling j initstage
 * UNCONFIRMED: arg types
 */
int initstage(int, int, int, int, int, int);

int stagemanager_restartstagecore(int a, int b, int c, int d) {
    return initstage(a, b, c, -1, d, 1);
}
