/* KERNEL.XFF @ 0x000EF0 (80 B) - func_000EF0 (static, no symbol in the shipped .symtab)
 * Evidence: calls each non-NULL entry of the two-function table at .bss+0x90B0. UNCONFIRMED: name; Ghidra FUN_00200ef0.
 */
extern void (*D_kernel_bss_090B0[2])(void);

void func_000EF0(void) {
    int i;

    for (i = 0; i < 2; i++) {
        if (D_kernel_bss_090B0[i]) {
            D_kernel_bss_090B0[i]();
        }
    }
}
