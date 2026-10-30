/* GAMECORE.XFF @ 0x0E0430 (44 B) - CAM_reset_aim_angle_rot
 * Evidence: `jal <.text>+0xE1618` with `$s0 = $a0`, `sw $zero -> +0x20`, tail `j
 * GAMEUTIL_reset_interp_ratio_cntrl` with `$a0 = $s0+0x24`.
 * UNCONFIRMED: struct field meanings and callee argument/return types
 
 */
void func_000E1618(void *p);
void GAMEUTIL_reset_interp_ratio_cntrl(void *p);

void CAM_reset_aim_angle_rot(char *p) {
    func_000E1618(p);
    *(int *)(p + 0x20) = 0;
    GAMEUTIL_reset_interp_ratio_cntrl(p + 0x24);
}
