/* KERNEL.XFF @ 0x003C28 (92 B) - iosDebugPartitionDump
 * Evidence: the static at .text+0x2FF0 is called as (root, 0, flags, -1), bracketed by WaitSema/SignalSema on the allocator semaphore (.bss+0x90B8, see iosWaitMalloc). UNCONFIRMED: callee prototype.
 */
extern int D_kernel_bss_90B8;
int WaitSema(int sema);
int SignalSema(int sema);
void func_002FF0(void *root, int depth, int flags, int max);

void iosDebugPartitionDump(void *root, int flags) {
    WaitSema(D_kernel_bss_90B8);
    func_002FF0(root, 0, flags, -1);
    SignalSema(D_kernel_bss_90B8);
}
