/* asm/cod/00FB20.s -> DIntr.
 * SCE libkernl DIntr; dtls13010 toolchain fills the final jr slot, the R5900 short-loop nop pair is explicit (Session 44)
 * MATCHED. */
int DIntr(void) {
    int intr;
    int stat;
    int res;

    __asm__ __volatile__ ("mfc0 %0, $12" : "=r" (intr));
    intr &= 0x10000;
    if (intr) {
        do {
            __asm__ __volatile__ ("di");
            __asm__ __volatile__ ("sync.p");
            __asm__ __volatile__ ("mfc0 %0, $12" : "=r" (stat));
            stat &= 0x10000;
            /* the original assembler's R5900 short-loop fix (no installed GAS
               also fills the final jr slot, see docs/decisions.md) */
            __asm__ __volatile__ ("nop\n\tnop" : "+r" (stat));
        } while (stat);
    }
    res = intr != 0;
    return res;
}
