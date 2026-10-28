/* KERNEL.XFF @ 0x003518 (296 B) - iosMallocGarbageTickProc
 * Evidence: under the allocator semaphore walks the block chain from the heap head (.data+0xB4; 24-bit next >> 2 at +8) while the continue callback(arg) returns non-zero; a free block (bit 0 of byte +0xF clear) followed by a garbage block whose callback field (+0x10, 24-bit, 0xFFFFFF = none) is set gets merged by the static at .text+0x18D8 and the callback is called with (arg field << 2, merged block). Bitfield layout shared with iosMallocSetExecGarbageCallback. UNCONFIRMED: names.
 */
extern int D_kernel_bss_90B8;
int WaitSema(int sema);
int SignalSema(int sema);
struct MemHdr {
    char pad[8];
    unsigned int next : 24;
    unsigned int f8 : 8;
    unsigned int fc : 24;
    unsigned int used : 1;
    unsigned int fc_hi : 7;
    unsigned int func : 24;
    unsigned int f10 : 8;
    unsigned int arg : 24;
    unsigned int f14 : 8;
};
extern struct MemHdr *D_kernel_data_00B4;
void *func_0018D8(struct MemHdr *h, struct MemHdr *n, struct MemHdr *heap);

void iosMallocGarbageTickProc(int (*cont)(void *), void *carg) {
    struct MemHdr *h;
    struct MemHdr *n;
    void (*func)(void *, void *);
    void *arg;

    WaitSema(D_kernel_bss_90B8);
    h = (struct MemHdr *)(D_kernel_data_00B4->next << 2);
    while (h != 0 && cont(carg)) {
        n = (struct MemHdr *)(h->next << 2);
        if (!(h->used) && n != 0 && (n->used) && n->func != 0xFFFFFF) {
            func = (void (*)(void *, void *))(n->func << 2);
            arg = (void *)(n->arg << 2);
            n = func_0018D8(h, n, D_kernel_data_00B4);
            if (func != 0) {
                func(arg, n);
            }
            n = (struct MemHdr *)(h->next << 2);
        }
        h = n;
    }
    SignalSema(D_kernel_bss_90B8);
}
