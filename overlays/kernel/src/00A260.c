/* KERNEL.XFF @ 0x00A260 (36 B) - func_00A260 (static, no symbol in the shipped .symtab)
 * Evidence: iosJumpRecoverPoint(.rodata+0xA28 message), returns 0 (a fatal stub). UNCONFIRMED: name; Ghidra FUN_0020a260.
 */
extern char D_kernel_rodata_0A28[];
void iosJumpRecoverPoint(const char *msg);

int func_00A260(void) {
    iosJumpRecoverPoint(D_kernel_rodata_0A28);
    return 0;
}
