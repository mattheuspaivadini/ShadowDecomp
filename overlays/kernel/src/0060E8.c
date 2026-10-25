/* KERNEL.XFF @ 0x0060E8 (100 B) - iosSprToMemDmaAdrCopy
 * Evidence: DMA channel 8 (fromSPR): D_PCR = -0x400, D_STAT = 0x100, D8_MADR, D8_QWC, D8_SADR, D_PCR |= 0x100, D8_CHCR = 0x100.
 */
void iosSprToMemDmaAdrCopy(unsigned int mem, int qwc, unsigned int spr) {
    *(volatile int *)0x1000E020 = -0x400;
    *(volatile int *)0x1000E010 = 0x100;
    *(volatile unsigned int *)0x1000D010 = mem;
    *(volatile int *)0x1000D020 = qwc;
    *(volatile unsigned int *)0x1000D080 = spr;
    *(volatile int *)0x1000E020 |= 0x100;
    *(volatile int *)0x1000D000 = 0x100;
}
