/* GAMECORE.XFF @ 0x00A758 (20 B) - GAMEUTIL_reset_status_manager
 * Evidence: stores a1 to +0/+4/+8, 0 to +0xC
 * UNCONFIRMED: none
 */
void GAMEUTIL_reset_status_manager(int *p, int v) {
    p[3] = 0;
    p[2] = v;
    p[1] = v;
    p[0] = v;
}
