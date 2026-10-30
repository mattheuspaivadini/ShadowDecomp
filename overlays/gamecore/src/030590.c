/* GAMECORE.XFF @ 0x030590 (16 B) - scriptNormalHook
 * Evidence: uses t0 ($8, 5th arg reg): [t0+0x14] += 1
 * UNCONFIRMED: signature
 */
void scriptNormalHook(int a, int b, int c, int d, int *t0) {
    t0[5] += 1;
}
