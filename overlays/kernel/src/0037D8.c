/* KERNEL.XFF @ 0x0037D8 (156 B) - iosMallocInGarbagePtn
 * Evidence: under the allocator semaphore, the static allocator .text+0x1428 gets (.data+0xB4 partition, size, align raised to at least 16, caller pc via $ra register variable); a non-NULL block gets the low 24 bits of its header word +0x10 set (garbage marker).
 */
extern int D_kernel_bss_90B8;
int WaitSema(int sema);
int SignalSema(int sema);
struct MemHdr {
    char pad[0x10];
    unsigned int garbage;
};
extern void *D_kernel_data_00B4;
void *func_001428(void *ptn, int size, int align, void *pc);

void *iosMallocInGarbagePtn(int size, int align) {
    register void *ra __asm__("$31");
    void *pc = ra;
    void *p;

    WaitSema(D_kernel_bss_90B8);
    if (align < 16) {
        align = 16;
    }
    p = func_001428(D_kernel_data_00B4, size, align, pc);
    if (p != 0) {
        ((struct MemHdr **)p)[-1]->garbage |= 0xFFFFFF;
    }
    SignalSema(D_kernel_bss_90B8);
    return p;
}
