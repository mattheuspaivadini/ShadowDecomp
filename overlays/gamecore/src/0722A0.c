/* GAMECORE.XFF @ 0x0722A0 (56 B) - nico_SmokemanBodyTexEnd
 * Evidence: `jal isysGetThisSubThread` (result -> $a0), `$a1 = .data+0x14A0`,
 * `$f12 = 0.0f`, `$f13 = 0xBD4CCCCC (-0.0075f)`, then a tail `j bootTexAlphaAnim`
 * with `addiu $sp` in the delay slot.
 * UNCONFIRMED: the `.data` object's name.
 
 */
void *isysGetThisSubThread(void);
void bootTexAlphaAnim(void *thread, void *data, float start, float rate);
extern char D_kernel_data_0000[];

void nico_SmokemanBodyTexEnd(void) {
    bootTexAlphaAnim(isysGetThisSubThread(), D_kernel_data_0000 + 0x14A0, 0.0f,
                     -0.0075f);
}
