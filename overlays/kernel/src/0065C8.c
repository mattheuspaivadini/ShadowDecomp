/* KERNEL.XFF @ 0x0065C8 (52 B) - iosGetThread
 * Evidence: `GetThreadId()` indexes a word table at .bss+0xB1A0 (`sll 2`, base kept
 * in $s0 across the call). UNCONFIRMED: table name/element type.
 */
int GetThreadId(void);
extern void *D_kernel_bss_B1A0[];

void *iosGetThread(void) {
    return D_kernel_bss_B1A0[GetThreadId()];
}
