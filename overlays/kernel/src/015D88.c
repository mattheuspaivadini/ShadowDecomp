/* KERNEL.XFF @ 0x015D88 (212 B) - iosDmaSendSChainPath3
 * Evidence: identical to iosDmaSendSChainPath1 except for the VIF1
 * registers: 0x1000A020 = 0, 0x1000A030 = addr & 0x7FFFFFFF and the final
 * 0x1000A000 = 0x105. UNCONFIRMED: register names.
 */
#define VIF0STAT (*(volatile unsigned int *)0x10009000)
#define VIF1STAT (*(volatile unsigned int *)0x1000A000)
#define VIF1ERR (*(volatile unsigned int *)0x1000A020)
#define VIF1BASE (*(volatile unsigned int *)0x1000A030)
#define DSTAT (*(volatile unsigned int *)0x10003C00)
#define DPCR (*(volatile unsigned int *)0x10003020)

extern void FlushCache(int mode);

void iosDmaSendSChainPath3(unsigned int addr) {
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
    VIF1ERR = 0;
    VIF1BASE = addr & 0x7FFFFFFF;
    FlushCache(0);
    VIF1STAT = 0x105;
}
