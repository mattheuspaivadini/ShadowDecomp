/* KERNEL.XFF @ 0x003878 (148 B) - iosMallocSetExecGarbageCallback
 * Evidence: under the allocator semaphore, the block header (p[-1]) gets func >> 2 and arg >> 2 in the 24-bit fields of words +0x10 and +0x14 (top bytes preserved: bitfields).
 */
extern int D_kernel_bss_90B8;
int WaitSema(int sema);
int SignalSema(int sema);
struct MemHdr {
    char pad[0x10];
    unsigned int func : 24;
    unsigned int f0 : 8;
    unsigned int arg : 24;
    unsigned int f1 : 8;
};

void iosMallocSetExecGarbageCallback(void *p, int func, int arg) {
    struct MemHdr *h;

    WaitSema(D_kernel_bss_90B8);
    h = ((struct MemHdr **)p)[-1];
    h->func = func >> 2;
    h->arg = arg >> 2;
    SignalSema(D_kernel_bss_90B8);
}
