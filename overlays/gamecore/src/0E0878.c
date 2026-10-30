/* GAMECORE.XFF @ 0x0E0878 (16 B) - CAM_motion_kind_is_mode_lock_target
 * Evidence: ops lw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
int CAM_motion_kind_is_mode_lock_target(char *p) {
    return (F(p, unsigned, 0x178) >> 5) & 1;
}
