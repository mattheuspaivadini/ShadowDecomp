/* GAMECORE.XFF @ 0x024F40 (64 B) - initSlowManager
 * Evidence: `lw 0($s0)` on `.data+0xB68` guards the body; `jal isysInitGroup`
 * with `$a0 = .bss+0x4AF0`, then `sw 1` back to the guard word.
 * UNCONFIRMED: the guard's name and the group block at `.bss+0x4AF0`.
 
 */
void isysInitGroup(void *group);
extern char D_kernel_data_0000[];
extern char D_kernel_bss_0000[];

void initSlowManager(void) {
    if (*(int *)(D_kernel_data_0000 + 0xB68) == 0) {
        isysInitGroup(D_kernel_bss_0000 + 0x4AF0);
        *(int *)(D_kernel_data_0000 + 0xB68) = 1;
    }
}
