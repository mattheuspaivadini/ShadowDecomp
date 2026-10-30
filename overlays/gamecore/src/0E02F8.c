/* GAMECORE.XFF @ 0x0E02F8 (12 B) - CAM_interp_reset_aim_rot_common
 * Evidence: ops sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void CAM_interp_reset_aim_rot_common(char *p) {
    F(p, int, 0x20) = 1;
}
