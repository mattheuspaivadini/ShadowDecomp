/* GAMECORE.XFF @ 0x0D3AE8 (60 B) - nico_yamoriLegLeftTexStart
 * Evidence: `jal isysGetThisSubThread`, `$f12 = 1.0f`,
 * `$f13 = 0.05f` (lui/ori 0x3D4CCCCC), `$a1 = <.data>+0x1D58`,
 * tail `j bootTexAlphaAnim`.
 * UNCONFIRMED: none
 
 */
int isysGetThisSubThread(void);
void bootTexAlphaAnim(int thread, void *tex, float from, float to);
extern char D_kernel_data_1D58[];

void nico_yamoriLegLeftTexStart(void) {
    bootTexAlphaAnim(isysGetThisSubThread(), D_kernel_data_1D58,
                     1.0f, 0.05f);
}
