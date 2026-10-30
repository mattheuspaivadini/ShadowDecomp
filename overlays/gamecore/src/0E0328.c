/* GAMECORE.XFF @ 0x0E0328 (44 B) - CAM_set_interp_param_aim_rot_common
 * Evidence: `lw [a0+0x20]` + `bnez` to the return path, `addiu $a0,$a0,0x24` in the delay slot,
 * tail `j GAMEUTIL_set_param_interp_ratio_cntrl`.
 * UNCONFIRMED: struct field meanings and callee argument/return types
 
 */
void GAMEUTIL_set_param_interp_ratio_cntrl(void *p);

void CAM_set_interp_param_aim_rot_common(char *p) {
    if (*(int *)(p + 0x20) == 0)
        GAMEUTIL_set_param_interp_ratio_cntrl(p + 0x24);
}
