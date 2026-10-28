/* KERNEL.XFF @ 0x015A08 (228 B) - iosDmaSendPath2
 * Evidence: byte-for-byte the same body as iosDmaSendPath1 (0x015920); the
 * two functions differ only in placement, so the draft is the same source with
 * the other name. UNCONFIRMED: register names.
 */
#define VIF0STAT (*(volatile unsigned int *)0x10009000)
#define VIF0FBRST (*(volatile unsigned int *)0x10009010)
#define VIF0ERR (*(volatile unsigned int *)0x10009020)
#define VIF1STAT (*(volatile unsigned int *)0x1000A000)
#define DSTAT (*(volatile unsigned int *)0x10003C00)
#define DPCR (*(volatile unsigned int *)0x10003020)

extern void FlushCache(int mode);

void iosDmaSendPath2(long addr, long size) {
    unsigned int vu0;

    while (1) {
        __asm__ volatile("cfc2.ni %0, $vi29" : "=r"(vu0));
        if (VIF0STAT & 0x100)
            continue;
        if (VIF1STAT & 0x100)
            continue;
        if (DSTAT & 0x1F000003)
            continue;
        if (vu0 & 0x100)
            continue;
        if (DPCR & 0xC00)
            continue;
        break;
    }
    VIF0ERR = size;
    VIF0FBRST = addr & 0xFFFFFFF;
    FlushCache(0);
    VIF0STAT = 0x101;
}
