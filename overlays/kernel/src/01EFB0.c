/* KERNEL.XFF @ 0x01EFB0 (28 B) - func_01EFB0 (static, no symbol in the shipped .symtab)
 * Evidence: tail call iSignalSema(.bss+0x7D440) - the keyboard RPC semaphore, used as an interrupt-context completion callback. UNCONFIRMED: name; Ghidra FUN_0021efb0.
 */
extern int D_kernel_bss_7D440;
int iSignalSema(int sema);

void func_01EFB0(void) {
    iSignalSema(D_kernel_bss_7D440);
}
