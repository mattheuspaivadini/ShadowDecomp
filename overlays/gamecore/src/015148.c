/* GAMECORE.XFF @ 0x015148 (60 B) - _gameFlagSet
 * Evidence: `slti`/`addiu 7`/`movn` sign-corrected `>> 3` index, `andi 7` +
 * `sllv` mask, `lbu`/`or`/`sb` on `.bss+0x3D0`, returning the unmasked OR
 * result in `$v0` with the store in the `jr` delay slot.
 * UNCONFIRMED: the flag byte array's name.
 
 */
extern unsigned char D_kernel_bss_0000[];

int _gameFlagSet(int index) {
    unsigned char *p = D_kernel_bss_0000 + 0x3D0 + index / 8;
    int mask = 1 << (index & 7);
    int value = *p | mask;

    *p = value;
    return value;
}
