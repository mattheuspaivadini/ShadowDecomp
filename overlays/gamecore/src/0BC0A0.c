/* GAMECORE.XFF @ 0x0BC0A0 (56 B) - nico_snakeBellyCenterTexEnd
 * Evidence: stores $ra, 0x0($sp); loads $ra, 0x0($sp); relocs <.data>; calls isysGetThisSubThread, j bootTexAlphaAnim; frame
 
 */
int isysGetThisSubThread(void);
void bootTexAlphaAnim(int thread, char *data, float a, float b);
extern char D_kernel_data_16F0[];

void nico_snakeBellyCenterTexEnd(void) {
    bootTexAlphaAnim(isysGetThisSubThread(), D_kernel_data_16F0, 0.0f, -0.05f);
}
