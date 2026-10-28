/* KERNEL.XFF @ 0x01B6E0 (36 B) - func_01B6E0 (static, no symbol in the shipped .symtab)
 * Evidence: tail call iosRecvMsg(.bss+0x791A8, 0, 0). UNCONFIRMED: name and argument types; Ghidra FUN_0021b6e0.
 */
extern char D_kernel_bss_791A8[];
int iosRecvMsg(void *box, void *msg, int mode);

int func_01B6E0(void) {
    return iosRecvMsg(D_kernel_bss_791A8, 0, 0);
}
