/* GAMECORE.XFF @ 0x0181C8 (64 B) - gameflowBossEyeCameraDisable
 * Evidence: `bne $a0,1` selects `*p + 1` vs `*p - 1` (both paths join at the
 * `sw`); then the value is re-read through a second register (`$a2`) and
 * `bltzl $v0` + `sw $zero,0($a2)` in the delay slot clamps it to 0.
 * UNCONFIRMED: the counter at `.data+0x7C4` and the meaning of the mode.
 */
extern char D_kernel_data_0000[];

void gameflowBossEyeCameraDisable(int mode) {
    int *p = (int *)(D_kernel_data_0000 + 0x7C4);

    if (mode == 1)
        *p = *p + 1;
    else
        *p = *p - 1;
    if (*(int *)(D_kernel_data_0000 + 0x7C4) < 0)
        *(int *)(D_kernel_data_0000 + 0x7C4) = 0;
}
