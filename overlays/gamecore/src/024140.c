/* GAMECORE.XFF @ 0x024140 (32 B) - UpdateSeamlessStageLoad
 * Evidence: if .data+0xA98 then .data+0xA90 = 1
 * UNCONFIRMED: none
 */
extern int D_kernel_data_0A90[];

void UpdateSeamlessStageLoad(void) {
    if (D_kernel_data_0A90[2])
        D_kernel_data_0A90[0] = 1;
}
