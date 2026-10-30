/* GAMECORE.XFF @ 0x0151C8 (48 B) - _gameFlagChk
 * Evidence: signed divide-by-8 idiom (`slti`/`addiu 7`/`movn`/`sra 3`) for the
 * byte index, explicit `andi 7` for the bit index, `lbu` from `.bss+0x3D0`
 * then `srav` and `andi 1`. `index % 8` canonicalises to `subu`/`sll` instead
 * of `andi`, so the source uses the explicit mask.
 * UNCONFIRMED: the flag array meaning.
 
 */
extern unsigned char D_kernel_bss_03D0[];

int _gameFlagChk(int index) {
    return (D_kernel_bss_03D0[index / 8] >> (index & 7)) & 1;
}
