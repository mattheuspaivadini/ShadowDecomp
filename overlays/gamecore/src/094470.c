/* GAMECORE.XFF @ 0x094470 (56 B) - nico_poseidonToothFTexAnimEnd
 * Evidence: `jal isysGetThisSubThread` (result -> $a0), `$a1 = .data+0x1618`,
 * `$f12 = 0.0f`, `$f13 = 0xBD4CCCCC (-0.05f)`, then a tail `j bootTexAlphaAnim`
 * with `addiu $sp` in the delay slot.
 * UNCONFIRMED: the `.data` object's name.
 
 */
void *isysGetThisSubThread(void);
void bootTexAlphaAnim(void *thread, void *data, float start, float rate);
extern char D_kernel_data_0000[];

void nico_poseidonToothFTexAnimEnd(void) {
    bootTexAlphaAnim(isysGetThisSubThread(), D_kernel_data_0000 + 0x1618, 0.0f,
                     -0.05f);
}
