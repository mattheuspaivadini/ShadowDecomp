/* GAMECORE.XFF @ 0x00A7C0 (32 B) - GAMEUTIL_is_status_change_status_manager
 * Evidence: c.le.s p[3],0 -> 1 else 0
 * UNCONFIRMED: none
 */
int GAMEUTIL_is_status_change_status_manager(float *p) {
    return p[3] <= 0.0f;
}
