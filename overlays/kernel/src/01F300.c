/* KERNEL.XFF @ 0x01F300 (28 B) - func_01F300 (static, no symbol in the shipped .symtab)
 * Evidence: tail call iSignalSema(.bss+0x7E520) - the mouse RPC semaphore, used as an interrupt-context completion callback. UNCONFIRMED: name; Ghidra FUN_0021f300.
 */
extern int D_kernel_bss_7E520;
int iSignalSema(int sema);

void func_01F300(void) {
    iSignalSema(D_kernel_bss_7E520);
}
