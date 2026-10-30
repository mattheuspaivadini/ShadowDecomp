/* GAMECORE.XFF @ 0x015BB0 (48 B) - _omakeGetFlagChk
 * Evidence: signed divide-by-8 idiom (`slti`/`addiu 7`/`movn`/`sra 3`) for the
 * byte index, explicit `andi 7` for the bit index, `lbu` from `.bss+0xC5A`
 * then `srav` and `andi 1`.
 * UNCONFIRMED: the flag array meaning.
 
 */
extern unsigned char D_kernel_bss_0C5A[];

int _omakeGetFlagChk(int index) {
    return (D_kernel_bss_0C5A[index / 8] >> (index & 7)) & 1;
}
