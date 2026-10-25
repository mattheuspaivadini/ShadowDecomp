/* KERNEL.XFF @ 0x006080 (104 B) - iosMemToSprDmaAdrCopy
 * Evidence: DMA channel 9 (toSPR): D_PCR = -0x400, D_STAT = 0x200, D9_MADR = mem, D9_QWC = qwc, D9_SADR = spr, D_PCR |= 0x200, D9_CHCR = 0x101 (all volatile, in order).
 */
void iosMemToSprDmaAdrCopy(unsigned int mem, int qwc, unsigned int spr) {
    *(volatile int *)0x1000E020 = -0x400;
    *(volatile int *)0x1000E010 = 0x200;
    *(volatile unsigned int *)0x1000D410 = mem;
    *(volatile int *)0x1000D420 = qwc;
    *(volatile unsigned int *)0x1000D480 = spr;
    *(volatile int *)0x1000E020 |= 0x200;
    *(volatile int *)0x1000D400 = 0x101;
}
