/* GAMECORE.XFF @ 0x0E3658 (20 B) - is_main_cameraman_exist
 * Evidence: ops lw; data <.bss>+-0x3E00
 * UNCONFIRMED: field names/types guessed from offsets
 */
extern int D_kernel_bss_1C200[];
int is_main_cameraman_exist(void) {
    return D_kernel_bss_1C200[0] != -1;
}
