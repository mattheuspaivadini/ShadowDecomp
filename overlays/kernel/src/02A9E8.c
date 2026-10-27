/* KERNEL.XFF @ 0x02A9E8 (100 B) - Sg2SlotSetNoiseOnBit
 * Evidence: ORs the bits into the per-core noise word at .bss+0x97E00 under DIntr/EIntr (EIntr only if interrupts were on); the element address is computed before DIntr (GAS la with index). UNCONFIRMED: table names.
 */
extern unsigned int D_kernel_bss_97E00[2];
int DIntr(void);
int EIntr(void);

void Sg2SlotSetNoiseOnBit(int core, unsigned int bits) {
    int intr = DIntr();

    D_kernel_bss_97E00[core] |= bits;
    if (intr) {
        EIntr();
    }
}
