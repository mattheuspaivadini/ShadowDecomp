/* STATUS (Session 41, 2026-10-21): NON_MATCHING. best score 3 (was 3; sw.py diff lines).
 * Zero path now goes through the return pseudo like the image (res = intr != 0 after the if: a0 = 0; v0 = a0). Remaining line = the last jr slot: cc1 emits this return in .set reorder mode, and the slot is a GAS decision. The -S output of 991111-01 and 991111-01-dtls13010 is identical; the 991111-01 as leaves the slot empty but adds the two R5900 short-loop nops, the dtls13010/2.96/3.2 as fill the slot but add no loop nops (build/s41/asy.sh). The image needs both, so no single installed toolchain reproduces it.
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
    int res;

    __asm__ __volatile__ ("mfc0 %0, $12" : "=r" (intr));
    intr &= 0x10000;
    if (intr) {
        do {
            __asm__ __volatile__ ("di");
            __asm__ __volatile__ ("sync.p");
            __asm__ __volatile__ ("mfc0 %0, $12" : "=r" (stat));
        } while (stat & 0x10000);
    }
    res = intr != 0;
    return res;
}
