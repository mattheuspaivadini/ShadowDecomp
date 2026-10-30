/* GAMECORE.XFF @ 0x0E0358 (44 B) - CAM_set_interp_param_extend_aim_rot_common
 * Evidence: same shape as 0E0328 with `GAMEUTIL_set_param_extend_interp_ratio_cntrl`.
 * UNCONFIRMED: struct field meanings and callee argument/return types
 
 */
void GAMEUTIL_set_param_extend_interp_ratio_cntrl(void *p);

void CAM_set_interp_param_extend_aim_rot_common(char *p) {
    if (*(int *)(p + 0x20) == 0)
        GAMEUTIL_set_param_extend_interp_ratio_cntrl(p + 0x24);
}
