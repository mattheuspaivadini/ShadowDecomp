/* KERNEL.XFF @ 0x0039D8 (112 B) - iosFreeParts
 * Evidence: the static at .text+0x24A8 gets (ptn, p, size) under the allocator semaphore (.bss+0x90B8), the result returned.
 */
extern int D_kernel_bss_90B8;
int WaitSema(int sema);
int SignalSema(int sema);
int func_0024A8(void *ptn, void *p, int size);

int iosFreeParts(void *ptn, void *p, int size) {
    int r;

    WaitSema(D_kernel_bss_90B8);
    r = func_0024A8(ptn, p, size);
    SignalSema(D_kernel_bss_90B8);
    return r;
}
