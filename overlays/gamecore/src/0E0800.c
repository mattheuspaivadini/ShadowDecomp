/* GAMECORE.XFF @ 0x0E0800 (16 B) - CAM_motion_kind_act_auto_yaw_rot_target
 * Evidence: ops lw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
int CAM_motion_kind_act_auto_yaw_rot_target(char *p) {
    return (F(p, unsigned, 0x174) >> 29) & 1;
}
