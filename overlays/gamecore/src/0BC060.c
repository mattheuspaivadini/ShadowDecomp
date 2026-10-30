/* GAMECORE.XFF @ 0x0BC060 (60 B) - nico_snakeBellyFrontTexStart
 * Evidence: stores $ra, 0x0($sp); loads $ra, 0x0($sp); relocs <.data>; calls isysGetThisSubThread, j bootTexAlphaAnim; frame
 
 */
int isysGetThisSubThread(void);
void bootTexAlphaAnim(int thread, char *data, float a, float b);
extern char D_kernel_data_16D8[];

void nico_snakeBellyFrontTexStart(void) {
    bootTexAlphaAnim(isysGetThisSubThread(), D_kernel_data_16D8, 1.0f, 0.05f);
}
