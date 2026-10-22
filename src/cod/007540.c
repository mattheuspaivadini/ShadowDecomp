/* asm/cod/007540.s -> DisableDmac.
 * SCE libkernl DisableDmac: the _DisableDmac syscall inside a DIntr/EIntr
 * bracket taken only when interrupts were enabled (Status.EIE, mfc0 $12).
 * MATCHED. */
int DIntr(void);
int EIntr(void);
int _DisableDmac(int ch);

int DisableDmac(int ch) {
    int intr;
    int ret;

    __asm__ __volatile__ ("mfc0 %0, $12" : "=r" (intr));
    intr &= 0x10000;
    if (intr)
        DIntr();
    ret = _DisableDmac(ch);
    __asm__ __volatile__ ("sync" ::: "memory");
    if (intr)
        EIntr();
    return ret;
}
