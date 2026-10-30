/* GAMECORE.XFF @ 0x0305A8 (16 B) - demoNormalHook
 * Evidence: uses t0 ($8, 5th arg reg): [t0+0x14] += 1
 * UNCONFIRMED: signature
 */
void demoNormalHook(int a, int b, int c, int d, int *t0) {
    t0[5] += 1;
}
