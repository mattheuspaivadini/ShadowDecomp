/* GAMECORE.XFF @ 0x096C50 (16 B) - bossCloudStart
 * Evidence: HI16/LO16 <.data> store
 * UNCONFIRMED: field names/types guessed from offsets
 */
extern int D_kernel_data_16C4[];

void bossCloudStart(void) {
    D_kernel_data_16C4[0] = 1;
}
