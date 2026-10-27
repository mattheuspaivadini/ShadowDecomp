/* KERNEL.XFF @ 0x0067F0 (64 B) - iosGetThreadPriority
 * Evidence: when the argument is NULL the current thread object comes from the
 * .bss+0xB1A0 table indexed by GetThreadId(); the `sw $zero,0x14($a0)` sits
 * after the join, so it runs on both paths; returns 0. UNCONFIRMED: the
 * object layout (+0x14) and why a "Get" routine clears it.
 */
int GetThreadId(void);
extern char *D_kernel_bss_B1A0[];

int iosGetThreadPriority(char *thread) {
    if (thread == 0) {
        thread = D_kernel_bss_B1A0[GetThreadId()];
    }
    *(int *)(thread + 0x14) = 0;
    return 0;
}
