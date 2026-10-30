/* GAMECORE.XFF @ 0x0E0C30 (56 B) - CAM_init_camera_warp_cntrl
 * Evidence: `lui 0x3DB2 / ori 0xB8C2` (5 degrees in radians; EE-GCC 2.96 truncates
 * `0.0872664626f` to that pattern) stored to +0x18 and +0x14, `sw $a1 -> +0`,
 * `sw $a2 -> +0xC`, `sw $a3 -> +0x1C`, tail `j <.text>+0xE0C68`.
 * UNCONFIRMED: struct field meanings and callee argument/return types
 
 */
void CAM_reset_camera_warp_cntrl(char *p);

void CAM_init_camera_warp_cntrl(char *p, int a, int b, int c) {
    *(int *)p = a;
    *(float *)(p + 0x14) = 0.0872664626f;
    *(int *)(p + 0x0C) = b;
    *(int *)(p + 0x1C) = c;
    *(float *)(p + 0x18) = 0.0872664626f;
    CAM_reset_camera_warp_cntrl(p);
}
