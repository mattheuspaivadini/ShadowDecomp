/* GAMECORE.XFF @ 0x0C85B8 (52 B) - CloseTimeAttackMenu
 * Evidence: build/s79/b/dis_all.txt (authority). mode == 1 sets the fixed
 * 0xFE bits, otherwise mode's bits are OR-ed into the same flag word at
 * D+0xC. Declaring the data symbol as int[] keeps +0xC as a displacement
 * (a char* base folds the offset into the %lo relocation instead).
 * UNCONFIRMED: the flag word's meaning.
 
 */
extern int D_kernel_data_1940[];

void CloseTimeAttackMenu(int bits) {
    if (bits == 1)
        D_kernel_data_1940[3] |= 0xFE;
    else
        D_kernel_data_1940[3] |= bits;
}
