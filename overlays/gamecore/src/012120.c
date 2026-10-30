/* GAMECORE.XFF @ 0x012120 (52 B) - CancelCaptionSubThreadAll
 * Evidence: `.data+0x738` is zeroed in the delay slot of `jal scrRun`, then
 * set to 1 afterwards.
 * UNCONFIRMED: the flag meaning.
 
 */
extern int D_kernel_data_0738;
void scrRun(void);

void CancelCaptionSubThreadAll(void) {
    D_kernel_data_0738 = 0;
    scrRun();
    D_kernel_data_0738 = 1;
}
