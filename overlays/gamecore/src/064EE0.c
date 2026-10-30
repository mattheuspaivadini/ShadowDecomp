/* GAMECORE.XFF @ 0x064EE0 (60 B) - nico_mammothLegLeftTexStart
 * Evidence: same shape as 064D78 with `$a1 = .data+0x1378`.
 * UNCONFIRMED: the `.data` object's name.
 
 */
void *isysGetThisSubThread(void);
void bootTexAlphaAnim(void *thread, void *data, float start, float rate);
extern char D_kernel_data_0000[];

void nico_mammothLegLeftTexStart(void) {
    bootTexAlphaAnim(isysGetThisSubThread(), D_kernel_data_0000 + 0x1378, 1.0f,
                     0.05f);
}
