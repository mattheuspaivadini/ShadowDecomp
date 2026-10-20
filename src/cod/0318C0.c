/* asm/cod/0318C0.s -> SyncDCache.
 * SCE libkernl SyncDCache: _sceSDC on the 64-byte aligned range inside
 * a DIntr/EIntr bracket taken only when interrupts were enabled (Status.EIE);
 * the 0xFFFFFFC0 mask comes out of gas as lui/ori.
 * MATCHED. */
int DIntr(void);
int EIntr(void);
void _sceSDC(unsigned int start, unsigned int end);

void SyncDCache(void *start, void *end) {
    int intr;

    __asm__ __volatile__ ("mfc0 %0, $12" : "=r" (intr));
    intr &= 0x10000;
    if (intr)
        DIntr();
    _sceSDC((unsigned int)start & 0xFFFFFFC0, (unsigned int)end & 0xFFFFFFC0);
    if (intr)
        EIntr();
}
