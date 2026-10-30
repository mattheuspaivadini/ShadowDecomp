/* GAMECORE.XFF @ 0x064DF0 (60 B) - nico_mammothArmLeftTexStart
 * Evidence: same shape as 064D78 with `$a1 = .data+0x1348`.
 * UNCONFIRMED: the `.data` object's name.
 
 */
void *isysGetThisSubThread(void);
void bootTexAlphaAnim(void *thread, void *data, float start, float rate);
extern char D_kernel_data_0000[];

void nico_mammothArmLeftTexStart(void) {
    bootTexAlphaAnim(isysGetThisSubThread(), D_kernel_data_0000 + 0x1348, 1.0f,
                     0.05f);
}
