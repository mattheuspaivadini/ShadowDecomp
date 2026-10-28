/* KERNEL.XFF @ 0x00A040 (36 B) - func_00A040 (static, no symbol in the shipped .symtab)
 * Evidence: tail call iosMallocAlign(loader partition .bss+0xDE60, size, align). UNCONFIRMED: name; Ghidra FUN_0020a040.
 */
extern void *D_kernel_bss_0DE60;
void *iosMallocAlign(void *ptn, int size, int align);

void *func_00A040(int size, int align) {
    return iosMallocAlign(D_kernel_bss_0DE60, size, align);
}
