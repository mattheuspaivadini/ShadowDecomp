/* asm/cod/031958.s -> _sceIDC.
 * SCE libkernl _sceIDC: _sceSDC twin that only invalidates matching
 * lines (cache 0x16) instead of writing them back.
 * MATCHED. */
void _sceIDC(unsigned int start, unsigned int end) {
    int i;
    unsigned int tag;

    for (i = 0; i < 0x1000; i += 0x40) {
        __asm__ __volatile__ ("sync");
        __asm__ __volatile__ ("cache 0x10, 0(%0)" : : "r" (i));
        __asm__ __volatile__ ("sync");
        __asm__ __volatile__ ("mfc0 %0, $28" : "=r" (tag));
        tag = (tag & 0xFFFFF000) + i;
        if (tag >= start && tag <= end) {
            __asm__ __volatile__ ("sync");
            __asm__ __volatile__ ("cache 0x16, 0(%0)" : : "r" (i));
            __asm__ __volatile__ ("sync");
        }
        __asm__ __volatile__ ("sync");
        __asm__ __volatile__ ("cache 0x10, 1(%0)" : : "r" (i));
        __asm__ __volatile__ ("sync");
        __asm__ __volatile__ ("mfc0 %0, $28" : "=r" (tag));
        tag = (tag & 0xFFFFF000) + i;
        if (tag >= start && tag <= end) {
            __asm__ __volatile__ ("sync");
            __asm__ __volatile__ ("cache 0x16, 1(%0)" : : "r" (i));
            __asm__ __volatile__ ("sync");
        }
        __asm__ __volatile__ ("sync");
    }
}
