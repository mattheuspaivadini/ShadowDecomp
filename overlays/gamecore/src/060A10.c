/* GAMECORE.XFF @ 0x060A10 (12 B) - ColCont_Reset
 * Evidence: sd zero -> +0; sw zero -> +8
 * UNCONFIRMED: none
 */
void ColCont_Reset(long *p) {
    *(int *)(p + 1) = 0;
    p[0] = 0;
}
