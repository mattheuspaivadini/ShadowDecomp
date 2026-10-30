/* GAMECORE.XFF @ 0x035F00 (12 B) - bootmccheckscriptNoBoot
 * Evidence: sw zero -> bss+0x69B8
 * UNCONFIRMED: none
 */
extern int D_kernel_bss_69B8[];

void bootmccheckscriptNoBoot(void) {
    D_kernel_bss_69B8[0] = 0;
}
