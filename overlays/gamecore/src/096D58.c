/* GAMECORE.XFF @ 0x096D58 (16 B) - bossDemoPlayerBreakDownAccept
 * Evidence: HI16/LO16 <.data> store
 * UNCONFIRMED: field names/types guessed from offsets
 */
extern int D_kernel_data_16CC[];

void bossDemoPlayerBreakDownAccept(void) {
    D_kernel_data_16CC[0] = 1;
}
