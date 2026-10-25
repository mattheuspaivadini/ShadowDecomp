/* KERNEL.XFF @ 0x0034F8 (28 B) - iosSignalMalloc
 * Evidence: frame + sibling `j SignalSema` with $a0 loaded from .bss+0x90B8 (the
 * semaphore iosWaitMalloc waits on). UNCONFIRMED: the object name.
 */
extern int D_kernel_bss_90B8;
int SignalSema(int sema);
void iosSignalMalloc(void) { SignalSema(D_kernel_bss_90B8); }
