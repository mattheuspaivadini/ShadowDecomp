/* KERNEL.XFF @ 0x015AF0 (228 B) - iosDmaSendPath3
 * Evidence: identical to iosDmaSendPath1 except for the VIF1 registers:
 * 0x1000A020 = size, 0x1000A010 = addr & 0xFFFFFFF and the final
 * 0x1000A000 = 0x141 instead of 0x101. UNCONFIRMED: register names.
 */
#define VIF0STAT (*(volatile unsigned int *)0x10009000)
#define VIF1STAT (*(volatile unsigned int *)0x1000A000)
#define VIF1FBRST (*(volatile unsigned int *)0x1000A010)
#define VIF1ERR (*(volatile unsigned int *)0x1000A020)
#define DSTAT (*(volatile unsigned int *)0x10003C00)
#define DPCR (*(volatile unsigned int *)0x10003020)

extern void FlushCache(int mode);

void iosDmaSendPath3(long addr, long size) {
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
    VIF1ERR = size;
    VIF1FBRST = addr & 0xFFFFFFF;
    FlushCache(0);
    VIF1STAT = 0x141;
}
