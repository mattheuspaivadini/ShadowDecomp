/* GAMECORE.XFF @ 0x015B30 (60 B) - _omakeGetFlagSet
 * Evidence: `slti`/`addiu 7`/`movn` sign-corrected `>> 3` index, `andi 7` +
 * `sllv` mask, `lbu`/`or`/`sb` on `.bss+0xC5A`, returning the unmasked OR
 * result in `$v0` with the store in the `jr` delay slot.
 * UNCONFIRMED: the flag byte array's name.
 
 */
extern unsigned char D_kernel_bss_0000[];

int _omakeGetFlagSet(int index) {
    unsigned char *p = D_kernel_bss_0000 + 0xC5A + index / 8;
    int mask = 1 << (index & 7);
    int value = *p | mask;

    *p = value;
    return value;
}
