/* GAMECORE.XFF @ 0x008CD8 (16 B) - GAMEUTIL_get_sight_on_reverse_cntrlLR_bool
 * Evidence: lw .data+0x0220, sltu v0,zero,v0
 * UNCONFIRMED: none
 */
extern int D_kernel_data_0220[];

int GAMEUTIL_get_sight_on_reverse_cntrlLR_bool(void) {
    return D_kernel_data_0220[0] != 0;
}
