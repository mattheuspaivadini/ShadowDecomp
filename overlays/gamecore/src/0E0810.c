/* GAMECORE.XFF @ 0x0E0810 (16 B) - CAM_motion_kind_is_accept_auto_rot_motion_target
 * Evidence: ops lw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
int CAM_motion_kind_is_accept_auto_rot_motion_target(char *p) {
    return (F(p, unsigned, 0x174) >> 30) & 1;
}
