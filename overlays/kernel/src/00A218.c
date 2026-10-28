/* KERNEL.XFF @ 0x00A218 (72 B) - func_00A218 (static, no symbol in the shipped .symtab)
 * Evidence: iosMallocAlign(rootPtn, size, 0x40); the byte counter at .data+0x370 grows by size; returns the block. UNCONFIRMED: name; Ghidra FUN_0020a218.
 */
extern char rootPtn[];
extern int D_kernel_data_0370;
void *iosMallocAlign(void *ptn, int size, int align);

void *func_00A218(int size) {
    void *p = iosMallocAlign(rootPtn, size, 0x40);

    D_kernel_data_0370 += size;
    return p;
}
