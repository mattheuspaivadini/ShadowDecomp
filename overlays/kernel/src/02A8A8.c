/* KERNEL.XFF @ 0x02A8A8 (100 B) - Sg2SlotSetKeyOffBit
 * Evidence: ORs the bits into the per-core key-off word at .bss+0x97DF8 under DIntr/EIntr (EIntr only if interrupts were on); the element address is computed before DIntr (GAS la with index). UNCONFIRMED: table names.
 */
extern unsigned int D_kernel_bss_97DF8[2];
int DIntr(void);
int EIntr(void);

void Sg2SlotSetKeyOffBit(int core, unsigned int bits) {
    int intr = DIntr();

    D_kernel_bss_97DF8[core] |= bits;
    if (intr) {
        EIntr();
    }
}
