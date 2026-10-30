/* GAMECORE.XFF @ 0x015188 (64 B) - _gameFlagCls
 * Evidence: same `slti`/`addiu 7`/`movn` sign-corrected `>> 3` index and
 * `andi 7` + `sllv` mask as _gameFlagSet, but the mask is inverted with
 * `nor` and the byte is cleared (`lbu`/`and`/`sb` on `.bss+0x3D0`, store in
 * the `jr` delay slot).
 * UNCONFIRMED: the flag byte array's name.
 
 */
extern unsigned char D_kernel_bss_0000[];

void _gameFlagCls(int index) {
    unsigned char *p = D_kernel_bss_0000 + 0x3D0 + index / 8;
    int mask = 1 << (index & 7);

    *p = *p & ~mask;
}
