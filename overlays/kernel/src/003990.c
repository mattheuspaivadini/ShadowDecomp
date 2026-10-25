/* KERNEL.XFF @ 0x003990 (68 B) - iosFree
 * Evidence: the static at .text+0x2018 releases the block, bracketed by WaitSema/SignalSema on the allocator semaphore (.bss+0x90B8, see iosWaitMalloc). UNCONFIRMED: callee name.
 */
extern int D_kernel_bss_90B8;
int WaitSema(int sema);
int SignalSema(int sema);
void func_002018(void *p);

void iosFree(void *p) {
    WaitSema(D_kernel_bss_90B8);
    func_002018(p);
    SignalSema(D_kernel_bss_90B8);
}
