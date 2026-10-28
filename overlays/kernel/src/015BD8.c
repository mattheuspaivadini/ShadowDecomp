/* KERNEL.XFF @ 0x015BD8 (212 B) - iosDmaSendSChainPath1
 * Evidence: the same five-poll loop as iosDmaSendPath1 (see 0x015920), then
 * VIF0 0x10009020 = 0, 0x10009030 = addr & 0x7FFFFFFF, FlushCache(0) and
 * 0x10009000 = 0x145. Only one argument is used, and it is masked, so the
 * parameter is a 32-bit address. UNCONFIRMED: register names.
 */
#define VIF0STAT (*(volatile unsigned int *)0x10009000)
#define VIF0FBRST (*(volatile unsigned int *)0x10009010)
#define VIF0ERR (*(volatile unsigned int *)0x10009020)
#define VIF0BASE (*(volatile unsigned int *)0x10009030)
#define VIF1STAT (*(volatile unsigned int *)0x1000A000)
#define DSTAT (*(volatile unsigned int *)0x10003C00)
#define DPCR (*(volatile unsigned int *)0x10003020)

extern void FlushCache(int mode);

void iosDmaSendSChainPath1(unsigned int addr) {
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
    VIF0ERR = 0;
    VIF0BASE = addr & 0x7FFFFFFF;
    FlushCache(0);
    VIF0STAT = 0x145;
}
