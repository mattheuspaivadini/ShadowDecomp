/* KERNEL.XFF @ 0x015920 (228 B) - iosDmaSendPath1
 * Evidence: five hardware polls (0x10009000 bit 0x100, 0x1000A000 bit 0x100,
 * 0x10003C00 mask 0x1F000003, the cfc2 $vi29 bit 0x100 read once per pass, and
 * 0x10003020 mask 0xC00) each `continue` back to the loop head, so the shipped
 * shape is one `while (1)` with five `continue` tests. The two register writes
 * (0x10009020 = size, 0x10009010 = addr & 0xFFFFFFF) are sign-extended from
 * 32 to 64 bits before the `sw` (dsll32/dsra32), which the compiler only emits
 * when the assigned value is `long` - i.e. both parameters are 64-bit.
 * FlushCache(0) then 0x10009000 = 0x101. UNCONFIRMED: register names.
 */
#define VIF0STAT (*(volatile unsigned int *)0x10009000)
#define VIF0FBRST (*(volatile unsigned int *)0x10009010)
#define VIF0ERR (*(volatile unsigned int *)0x10009020)
#define VIF1STAT (*(volatile unsigned int *)0x1000A000)
#define DSTAT (*(volatile unsigned int *)0x10003C00)
#define DPCR (*(volatile unsigned int *)0x10003020)

extern void FlushCache(int mode);

void iosDmaSendPath1(long addr, long size) {
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
