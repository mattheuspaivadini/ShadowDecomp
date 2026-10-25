/* KERNEL.XFF @ 0x0034D8 (28 B) - iosWaitMalloc
 * Evidence: frame + sibling `j WaitSema` with $a0 loaded from .bss+0x90B8, the
 * allocator semaphore (shared with iosSignalMalloc).
 * UNCONFIRMED: the object name.
 */
extern int D_kernel_bss_90B8;
int WaitSema(int sema);
void iosWaitMalloc(void) { WaitSema(D_kernel_bss_90B8); }
