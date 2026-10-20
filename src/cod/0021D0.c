/* asm/cod/0021D0.s -> setCop0Epc.
 * Loader helper: write EPC (COP0 $14). No direct jal to it in the image.
 * MATCHED. */
void setCop0Epc(int epc) {
    __asm__ __volatile__ ("mtc0 %0, $14" : : "r" (epc));
}
