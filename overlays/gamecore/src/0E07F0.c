/* GAMECORE.XFF @ 0x0E07F0 (16 B) - CAM_motion_kind_is_look_around_motion_target
 * Evidence: ops lw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
int CAM_motion_kind_is_look_around_motion_target(char *p) {
    return (F(p, unsigned, 0x174) >> 28) & 1;
}
