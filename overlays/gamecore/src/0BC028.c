/* GAMECORE.XFF @ 0x0BC028 (56 B) - nico_snakeBellyFrontTexEnd
 * Evidence: stores $ra, 0x0($sp); loads $ra, 0x0($sp); relocs <.data>; calls isysGetThisSubThread, j bootTexAlphaAnim; frame
 
 */
int isysGetThisSubThread(void);
void bootTexAlphaAnim(int thread, char *data, float a, float b);
extern char D_kernel_data_16D8[];

void nico_snakeBellyFrontTexEnd(void) {
    bootTexAlphaAnim(isysGetThisSubThread(), D_kernel_data_16D8, 0.0f, -0.05f);
}
