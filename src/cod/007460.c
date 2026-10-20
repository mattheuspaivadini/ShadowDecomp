/* asm/cod/007460.s -> QueryIntrContext.
 * SCE libkernl QueryIntrContext: nonzero unless Status.EXL is set (mfc0 $12).
 * MATCHED. */
int QueryIntrContext(void) {
    int stat;

    __asm__ __volatile__ ("mfc0 %0, $12" : "=r" (stat));
    return (stat ^ 1) & 1;
}
