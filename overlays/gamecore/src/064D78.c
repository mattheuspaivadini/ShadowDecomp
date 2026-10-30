/* GAMECORE.XFF @ 0x064D78 (60 B) - nico_mammothArmRightTexStart
 * Evidence: `jal isysGetThisSubThread` (result -> $a0), `$a1 = .data+0x1330`,
 * `$f12 = 0x3F800000 (1.0f)`, `$f13 = 0x3D4CCCCD (0.05f)`, then a tail
 * `j bootTexAlphaAnim` with `addiu $sp` in the delay slot. Same shape as the
 * 56 B `...TexEnd` twin, which only differs by using `mtc1 $zero` for the
 * start value.
 * UNCONFIRMED: the `.data` object's name.
 
 */
void *isysGetThisSubThread(void);
void bootTexAlphaAnim(void *thread, void *data, float start, float rate);
extern char D_kernel_data_0000[];

void nico_mammothArmRightTexStart(void) {
    bootTexAlphaAnim(isysGetThisSubThread(), D_kernel_data_0000 + 0x1330, 1.0f,
                     0.05f);
}
