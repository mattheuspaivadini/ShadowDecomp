/* KERNEL.XFF @ 0x01E678 (340 B) - sndBDOpen
 * Evidence: 5 args (a0 ctx, a1 getSize callback -> $s7, a2 iop channel -> $s6,
 * a3 alloc size -> iosAllocIopHeap, t0 wait callback -> $s1). iosAllocIopHeap's
 * NULL result falls into iosJumpRecoverPoint(.rodata+0x2AC0). The chunk loop
 * re-enters at jalr $s7 and stores the returned size in $s2; iosEE2IopRequest
 * takes the stack int at 0($sp) that iosEE2IopEndChk then reads. Both wait
 * loops are `while (cond == 0) { ... }` - that form (not do/while) is what
 * produces the rotated layout with the redundant `b` before the body and the
 * test at the bottom. Sg2DmaTransVoice(iop, ctx->0x10 + total, size), then
 * Sg2DmaTransStatus; if the wait callback is NULL the else branch runs
 * iosWaitIdleThread. Tail: ctx->4 >= 0 && ctx->0x10 -> Sg2VabBdOpen, then
 * iosFreeIopHeap.
 * UNCONFIRMED: struct/field names, prototype, .rodata string at 0x2AC0.
 */
typedef struct {
    int mode;
    int id;
    char pad[8];
    int addr;
} SndBd;

extern char D_kernel_rodata_2AC0[];

extern int iosAllocIopHeap(int size);
extern void iosFreeIopHeap(int addr);
extern void iosJumpRecoverPoint(const char *msg);
extern void iosEE2IopRequest(int chan, int addr, int size, int *req);
extern int iosEE2IopEndChk(int req);
extern void iosWaitIdleThread(void);
extern int Sg2DmaTransVoice(int dst, int src, int size);
extern int Sg2DmaTransStatus(int id);
extern void Sg2VabBdOpen(int id, int addr);

void sndBDOpen(SndBd *p, int (*getSize)(void), int chan, int size,
               void (*waitCb)(void)) {
    int total = 0;
    int n;
    int iop;
    int dma;
    int req;

    iop = iosAllocIopHeap(size);
    if (iop == 0) {
        iosJumpRecoverPoint(D_kernel_rodata_2AC0);
    }
    while ((n = getSize()) != 0) {
        iosEE2IopRequest(chan, iop, n, &req);
        while (iosEE2IopEndChk(req) == 0) {
            if (waitCb != 0) {
                waitCb();
            }
        }
        dma = Sg2DmaTransVoice(iop, p->addr + total, n);
        while (Sg2DmaTransStatus(dma) != 0) {
            if (waitCb == 0) {
                iosWaitIdleThread();
            } else {
                waitCb();
            }
        }
        total += n;
    }
    if (p->id >= 0 && p->addr != 0) {
        Sg2VabBdOpen(p->id, p->addr);
    }
    iosFreeIopHeap(iop);
}
