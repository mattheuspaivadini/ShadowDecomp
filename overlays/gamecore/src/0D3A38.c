/* GAMECORE.XFF @ 0x0D3A38 (56 B) - nico_yamoriLegRightTexEnd
 * Evidence: `jal isysGetThisSubThread`, `$f12 = 0.0f`,
 * `$f13 = -0.05f` (lui/ori 0xBD4CCCCC), `$a1 = <.data>+0x1D40`,
 * tail `j bootTexAlphaAnim`.
 * UNCONFIRMED: none
 
 */
int isysGetThisSubThread(void);
void bootTexAlphaAnim(int thread, void *tex, float from, float to);
extern char D_kernel_data_1D40[];

void nico_yamoriLegRightTexEnd(void) {
    bootTexAlphaAnim(isysGetThisSubThread(), D_kernel_data_1D40,
                     0.0f, -0.05f);
}
