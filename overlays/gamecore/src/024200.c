/* GAMECORE.XFF @ 0x024200 (32 B) - GetStageChipNum
 * Evidence: if .data+0xA98 return .data+0xAE8 else 0
 * UNCONFIRMED: none
 */
extern int D_kernel_data_0A90[];

int GetStageChipNum(void) {
    int *p = D_kernel_data_0A90;
    if (!p[2])
        return 0;
    return p[22];
}
