/* asm/cod/00FB70.s -> EIntr.
 * SCE libkernl EIntr: ei, returning whether interrupts were already enabled
 * (Status.EIE, mfc0 $12).
 * MATCHED. */
int EIntr(void) {
    int stat;

    __asm__ __volatile__ ("mfc0 %0, $12" : "=r" (stat));
    stat &= 0x10000;
    __asm__ __volatile__ ("ei");
    return stat != 0;
}
