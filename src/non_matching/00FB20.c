/* STATUS (Session 38, 2026-10-20): NON_MATCHING. best score 3 [cc=29].
 * SCE libkernl DIntr; di and sync.p as separate asm (one asm makes the loop look short and adds
 * the R5900 nop). Residual: the original keeps two return blocks (jr after the loop and after the
 * zero path, both moving a0 to v0); ours shares one. Tried ret local, if/else ret, early returns.
 * The original .s stays in the build (asm/cod/00FB20.s); this C
 * draft (Session 38) is kept for the record. */
/* asm/cod/00FB20.s -> DIntr.
 * SCE libkernl DIntr: if interrupts are enabled (Status.EIE), di/sync.p until
 * Status reads them disabled; returns whether they were enabled. di and
 * sync.p are separate asm statements (see sbrk 011FD0).
 */
int DIntr(void) {
    int intr;
    int stat;

    __asm__ __volatile__ ("mfc0 %0, $12" : "=r" (intr));
    intr &= 0x10000;
    if (intr) {
        do {
            __asm__ __volatile__ ("di");
            __asm__ __volatile__ ("sync.p");
            __asm__ __volatile__ ("mfc0 %0, $12" : "=r" (stat));
        } while (stat & 0x10000);
        return intr != 0;
    }
    return intr != 0;
}
