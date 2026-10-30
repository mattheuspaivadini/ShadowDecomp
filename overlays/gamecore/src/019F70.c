/* GAMECORE.XFF @ 0x019F70 (36 B) - gstatBootMcChkExistNicoData
 * Evidence: `lw $v0, 0($a0)`, `beql $v0, $zero` skipping the store, an `sw` of
 * .data+0x9EC into `0($a0)`, then `lw $v0, .data+0x9E8` in the return slot.
 * UNCONFIRMED: the two .data field meanings.
 
 */
extern int D_kernel_data_09E8[];
extern int D_kernel_data_09EC[];

int gstatBootMcChkExistNicoData(int *flag) {
    if (*flag != 0) {
        *flag = D_kernel_data_09EC[0];
    }
    return D_kernel_data_09E8[0];
}
