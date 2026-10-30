/* GAMECORE.XFF @ 0x008D08 (16 B) - GAMEUTIL_get_sight_on_reverse_cntrlUD_bool
 * Evidence: lw .data+0x0224, sltu v0,zero,v0
 * UNCONFIRMED: none
 */
extern int D_kernel_data_0224[];

int GAMEUTIL_get_sight_on_reverse_cntrlUD_bool(void) {
    return D_kernel_data_0224[0] != 0;
}
