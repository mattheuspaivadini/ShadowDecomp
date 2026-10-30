/* GAMECORE.XFF @ 0x015CC0 (48 B) - _omakeSelectFlagChk
 * Evidence: signed divide-by-8 idiom (`slti`/`addiu 7`/`movn`/`sra 3`) for the
 * byte index, explicit `andi 7` for the bit index, `lbu` from `.bss+0xC62`
 * then `srav` and `andi 1`.
 * UNCONFIRMED: the flag array meaning.
 
 */
extern unsigned char D_kernel_bss_0C62[];

int _omakeSelectFlagChk(int index) {
    return (D_kernel_bss_0C62[index / 8] >> (index & 7)) & 1;
}
