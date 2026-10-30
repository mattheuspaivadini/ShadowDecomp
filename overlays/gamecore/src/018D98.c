/* GAMECORE.XFF @ 0x018D98 (44 B) - gameModeInit
 * Evidence: `memset(.bss+0xD70, 0, 0x20)` and a `sw $zero` into .data+0x940
 * (the store is placed in the tail-call delay slot).
 * UNCONFIRMED: the two blocks' meanings and the callee prototype.
 
 */
extern char D_kernel_bss_0D70[];
extern int D_kernel_data_0940[];
void memset(void *dst, int value, unsigned int size);

void gameModeInit(void) {
    D_kernel_data_0940[0] = 0;
    memset(D_kernel_bss_0D70, 0, 0x20);
}
