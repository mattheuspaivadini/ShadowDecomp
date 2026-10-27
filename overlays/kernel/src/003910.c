/* KERNEL.XFF @ 0x003910 (128 B) - iosReallocAlign
 * Evidence: the static at .text+0x2830 gets (ptn, p, size, align) under the allocator semaphore (.bss+0x90B8), the result returned.
 */
extern int D_kernel_bss_90B8;
int WaitSema(int sema);
int SignalSema(int sema);
void *func_002830(void *ptn, void *p, int size, int align);

void *iosReallocAlign(void *ptn, void *p, int size, int align) {
    void *r;

    WaitSema(D_kernel_bss_90B8);
    r = func_002830(ptn, p, size, align);
    SignalSema(D_kernel_bss_90B8);
    return r;
}
