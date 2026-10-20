/* asm/cod/010390.s -> SetT2.
 * SCE libkernl SetT2 (kernel-mode helper behind SetT2_COUNT/MODE/COMP): with
 * interrupts disabled (di/sync.p until Status.EIE reads clear) and Status
 * EXL set, store val to the timer-2 register, then eret to $ra via ErrorEPC.
 * di/sync.p/mfc0 in the loop are one asm statement: as separate statements
 * the loop gets an extra R5900 short-loop nop
 *
 * MATCHED. */
void SetT2(volatile int *reg, int val) {
    int intr;
    int stat;

    __asm__ __volatile__ ("mfc0 %0, $12" : "=r" (intr));
    intr &= 0x10000;
    if (intr) {
        do {
            __asm__ __volatile__ ("di
	sync.p
	mfc0 %0, $12" : "=r" (stat));
        } while (stat & 0x10000);
    }
    __asm__ __volatile__ ("mfc0 %0, $12" : "=r" (stat));
    __asm__ __volatile__ ("sync.p");
    stat = ((stat | 6) ^ 2) | intr;
    __asm__ __volatile__ ("mtc0 %0, $12" : : "r" (stat));
    __asm__ __volatile__ ("sync.p");
    *reg = val;
    __asm__ __volatile__ ("mtc0 $31, $30");
    __asm__ __volatile__ ("sync.p");
    __asm__ __volatile__ ("eret");
}
