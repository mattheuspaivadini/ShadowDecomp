/* GAMECORE.XFF @ 0x0E0E50 (12 B) - CAM_act_warp_order_camera_warp_cntrl
 * Evidence: ops sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void CAM_act_warp_order_camera_warp_cntrl(char *p) {
    F(p, int, 0x28) = 1;
}
