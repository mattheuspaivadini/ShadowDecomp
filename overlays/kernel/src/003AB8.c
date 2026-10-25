/* KERNEL.XFF @ 0x003AB8 (112 B) - iosCreatePartitionWithPc
 * Evidence: the static at .text+0x2A80 gets (parent, size, pc) with an explicit pc under the allocator semaphore (.bss+0x90B8), the result returned.
 */
extern int D_kernel_bss_90B8;
int WaitSema(int sema);
int SignalSema(int sema);
void *func_002A80(void *parent, int size, void *pc);

void *iosCreatePartitionWithPc(void *parent, int size, void *pc) {
    void *r;

    WaitSema(D_kernel_bss_90B8);
    r = func_002A80(parent, size, pc);
    SignalSema(D_kernel_bss_90B8);
    return r;
}
