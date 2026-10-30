/* GAMECORE.XFF @ 0x012158 (52 B) - QuitCaptionSubThreadAll
 * Evidence: `.data+0x740` is set to 1 in the delay slot of `jal scrRun`, then
 * zeroed afterwards.
 * UNCONFIRMED: the flag meaning.
 
 */
extern int D_kernel_data_0740;
void scrRun(void);

void QuitCaptionSubThreadAll(void) {
    D_kernel_data_0740 = 1;
    scrRun();
    D_kernel_data_0740 = 0;
}
