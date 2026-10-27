/* KERNEL.XFF @ 0x003C88 (104 B) - iosDebugPartitionFileDump
 * Evidence: under the allocator semaphore, the static dumper at .text+0x2FF0 gets (root, 0, flags, fd).
 */
extern int D_kernel_bss_90B8;
int WaitSema(int sema);
int SignalSema(int sema);
void func_002FF0(void *root, int depth, int flags, int fd);

void iosDebugPartitionFileDump(void *root, int flags, int fd) {
    WaitSema(D_kernel_bss_90B8);
    func_002FF0(root, 0, flags, fd);
    SignalSema(D_kernel_bss_90B8);
}
