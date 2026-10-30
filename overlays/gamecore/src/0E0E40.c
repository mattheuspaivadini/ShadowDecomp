/* GAMECORE.XFF @ 0x0E0E40 (12 B) - CAM_set_invisible_warp_apply_range_camera_warp_cntrl
 * Evidence: ops swc1
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void CAM_set_invisible_warp_apply_range_camera_warp_cntrl(char *p, float a, float b) {
    F(p, float, 0x14) = a;
    F(p, float, 0x18) = b;
}
