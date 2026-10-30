/* GAMECORE.XFF @ 0x019718 (48 B) - gStatSaveDataGameFlagChk
 * Evidence: signed divide-by-8 idiom (`slti`/`addiu 7`/`movn`/`sra 3`) for the
 * byte index, explicit `andi 7` for the bit index, `lbu` from `.bss+0xD90`
 * then `srav` and `andi 1`.
 * UNCONFIRMED: the flag array meaning.
 
 */
extern unsigned char D_kernel_bss_0D90[];

int gStatSaveDataGameFlagChk(int index) {
    return (D_kernel_bss_0D90[index / 8] >> (index & 7)) & 1;
}
