/* GAMECORE.XFF @ 0x06D790 (12 B) - DirectTurn_Reset
 * Evidence: sw zero -> +0x10; sb zero -> +0x14
 * UNCONFIRMED: none
 */
void DirectTurn_Reset(char *p) {
    p[0x14] = 0;
    *(int *)(p + 0x10) = 0;
}
