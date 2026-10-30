/* GAMECORE.XFF @ 0x094430 (60 B) - nico_poseidonToothFTexAnimStrat
 * Evidence: same shape as 064D78 with `$a1 = .data+0x1618`.
 * UNCONFIRMED: the `.data` object's name (the symbol name is spelled
 * "Strat" in the image's symbol table, kept verbatim).
 
 */
void *isysGetThisSubThread(void);
void bootTexAlphaAnim(void *thread, void *data, float start, float rate);
extern char D_kernel_data_0000[];

void nico_poseidonToothFTexAnimStrat(void) {
    bootTexAlphaAnim(isysGetThisSubThread(), D_kernel_data_0000 + 0x1618, 1.0f,
                     0.05f);
}
