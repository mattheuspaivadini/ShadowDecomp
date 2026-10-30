/* GAMECORE.XFF @ 0x0DA398 (12 B) - CAM_get_interp_slope_pitch_ofst
 * Evidence: ops lwc1
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
float CAM_get_interp_slope_pitch_ofst(char *p) {
    return -F(p, float, 0x1C);
}
