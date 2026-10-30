/* GAMECORE.XFF @ 0x060DA0 (16 B) - MotSpdCtrl_Reset
 * Evidence: sb 0 -> +0x11,+0x10; sw 0 -> +0
 * UNCONFIRMED: none
 */
void MotSpdCtrl_Reset(char *p) {
    p[0x10] = 0;
    *(int *)p = 0;
    p[0x11] = 0;
}
