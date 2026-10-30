/* GAMECORE.XFF @ 0x0E07C0 (24 B) - CAM_get_motion_kind_interp_timer_target
 * Evidence: ops ld sd; calls j GAMEUTIL_get_interp_timer_interp_ratio_cntrl; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
float GAMEUTIL_get_interp_timer_interp_ratio_cntrl(char *p);
float CAM_get_motion_kind_interp_timer_target(char *p) {
    return GAMEUTIL_get_interp_timer_interp_ratio_cntrl(p + 8);
}
