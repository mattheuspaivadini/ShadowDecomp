/* GAMECORE.XFF @ 0x01D890 (16 B) - opflowChkAbort
 * Evidence: bss+0x4AD0 != 0
 * UNCONFIRMED: none
 */
extern int D_kernel_bss_4AD0[];

int opflowChkAbort(void) {
    return D_kernel_bss_4AD0[0] != 0;
}
