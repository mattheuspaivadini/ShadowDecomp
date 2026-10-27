/* KERNEL.XFF @ 0x003BD0 (88 B) - iosFollowAllLink
 * Evidence: a stack counter (0) is passed by address to the static walker at .text+0x32F8 (root, 0, &count) and returned, bracketed by WaitSema/SignalSema on the allocator semaphore (.bss+0x90B8, see iosWaitMalloc). UNCONFIRMED: callee prototype.
 */
extern int D_kernel_bss_90B8;
int WaitSema(int sema);
int SignalSema(int sema);
void func_0032F8(void *root, int depth, int *count);

int iosFollowAllLink(void *root) {
    int count = 0;

    WaitSema(D_kernel_bss_90B8);
    func_0032F8(root, 0, &count);
    SignalSema(D_kernel_bss_90B8);
    return count;
}
