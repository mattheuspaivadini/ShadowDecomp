/* asm/cod/007470.s -> DisableIntc.
 * SCE libkernl DisableIntc: the _DisableIntc syscall inside a DIntr/EIntr
 * bracket taken only when interrupts were enabled (Status.EIE, mfc0 $12).
 * MATCHED. */
int DIntr(void);
int EIntr(void);
int _DisableIntc(int ch);

int DisableIntc(int ch) {
    int intr;
    int ret;

    __asm__ __volatile__ ("mfc0 %0, $12" : "=r" (intr));
    intr &= 0x10000;
    if (intr)
        DIntr();
    ret = _DisableIntc(ch);
    __asm__ __volatile__ ("sync" ::: "memory");
    if (intr)
        EIntr();
    return ret;
}
