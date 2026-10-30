/* GAMECORE.XFF @ 0x064EA8 (56 B) - nico_mammothLegLeftTexEnd
 * Evidence: `jal isysGetThisSubThread` (result -> $a0), `$a1 = .data+0x1378`,
 * `$f12 = 0.0f`, `$f13 = 0xBD4CCCCC (-0.05f)`, then a tail `j bootTexAlphaAnim`
 * with `addiu $sp` in the delay slot.
 * UNCONFIRMED: the `.data` object's name.
 
 */
void *isysGetThisSubThread(void);
void bootTexAlphaAnim(void *thread, void *data, float start, float rate);
extern char D_kernel_data_0000[];

void nico_mammothLegLeftTexEnd(void) {
    bootTexAlphaAnim(isysGetThisSubThread(), D_kernel_data_0000 + 0x1378, 0.0f,
                     -0.05f);
}
