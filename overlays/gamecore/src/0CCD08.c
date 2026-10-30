/* GAMECORE.XFF @ 0x0CCD08 (56 B) - nico_eelHigeTexEnd
 * Evidence: `jal isysGetThisSubThread`, `$f12 = 0.0f`,
 * `$f13 = -0.05f` (lui/ori 0xBD4CCCCC), `$a1 = <.data>+0x1A68`,
 * tail `j bootTexAlphaAnim`.
 * UNCONFIRMED: none
 
 */
int isysGetThisSubThread(void);
void bootTexAlphaAnim(int thread, void *tex, float from, float to);
extern char D_kernel_data_1A68[];

void nico_eelHigeTexEnd(void) {
    bootTexAlphaAnim(isysGetThisSubThread(), D_kernel_data_1A68,
                     0.0f, -0.05f);
}
