/* asm/cod/031A00.s -> InvalidDCache.
 * SCE libkernl InvalidDCache: SyncDCache twin calling _sceIDC.
 * MATCHED. */
int DIntr(void);
int EIntr(void);
void _sceIDC(unsigned int start, unsigned int end);

void InvalidDCache(void *start, void *end) {
    int intr;

    __asm__ __volatile__ ("mfc0 %0, $12" : "=r" (intr));
    intr &= 0x10000;
    if (intr)
        DIntr();
    _sceIDC((unsigned int)start & 0xFFFFFFC0, (unsigned int)end & 0xFFFFFFC0);
    if (intr)
        EIntr();
}
