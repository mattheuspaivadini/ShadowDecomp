/* asm/cod/0075A8.s -> EnableDmac.
 * SCE libkernl EnableDmac: the _EnableDmac syscall inside a DIntr/EIntr
 * bracket taken only when interrupts were enabled (Status.EIE, mfc0 $12).
 * MATCHED. */
int DIntr(void);
int EIntr(void);
int _EnableDmac(int ch);

int EnableDmac(int ch) {
    int intr;
    int ret;

    __asm__ __volatile__ ("mfc0 %0, $12" : "=r" (intr));
    intr &= 0x10000;
    if (intr)
        DIntr();
    ret = _EnableDmac(ch);
    __asm__ __volatile__ ("sync" ::: "memory");
    if (intr)
        EIntr();
    return ret;
}
