/* GAMECORE.XFF @ 0x0E0308 (24 B) - CAM_set_clip_max_rot_vel_aim_rot_common
 * Evidence: ops swc1
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void CAM_set_clip_max_rot_vel_aim_rot_common(char *p, float v) {
    F(p, float, 0xC) = v * 0.017453293f;
}
