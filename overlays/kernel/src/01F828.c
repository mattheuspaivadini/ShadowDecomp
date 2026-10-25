/* KERNEL.XFF @ 0x01F828 (100 B) - Sg2CtrlTickProc
 * Evidence: ++tick counter (.bss+0x7F5C0), then the 16 {func, count} entries at .bss+0x7F540 are called in order and each count is incremented after its call.
 */
struct TickProc {
    void (*func)(void);
    int count;
};
extern struct TickProc D_kernel_bss_7F540[16];
extern int D_kernel_bss_7F5C0;

void Sg2CtrlTickProc(void) {
    struct TickProc *p;
    int i;

    D_kernel_bss_7F5C0++;
    p = D_kernel_bss_7F540;
    for (i = 15; i >= 0; i--, p++) {
        p->func();
        p->count++;
    }
}
