/* asm/cod/031818.s -> _sceSDC.
 * SCE libkernl _sceSDC: walk both ways of the 64-line EE data cache
 * (index load tag, cache 0x10), read TagLo ($28) and write back + invalidate
 * (cache 0x14) every line whose tag address lies in [start, end]. Each cache
 * op is bracketed by sync asm statements.
 * MATCHED. */
void _sceSDC(unsigned int start, unsigned int end) {
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
            __asm__ __volatile__ ("cache 0x14, 0(%0)" : : "r" (i));
            __asm__ __volatile__ ("sync");
        }
        __asm__ __volatile__ ("sync");
        __asm__ __volatile__ ("cache 0x10, 1(%0)" : : "r" (i));
        __asm__ __volatile__ ("sync");
        __asm__ __volatile__ ("mfc0 %0, $28" : "=r" (tag));
        tag = (tag & 0xFFFFF000) + i;
        if (tag >= start && tag <= end) {
            __asm__ __volatile__ ("sync");
            __asm__ __volatile__ ("cache 0x14, 1(%0)" : : "r" (i));
            __asm__ __volatile__ ("sync");
        }
        __asm__ __volatile__ ("sync");
    }
}
