/* KERNEL.XFF @ 0x02A840 (100 B) - Sg2SlotSetKeyOnBit
 * Evidence: ORs the bits into the per-core key-on word at .bss+0x97DF0 under DIntr/EIntr (EIntr only if interrupts were on); the element address is computed before DIntr (GAS la with index). UNCONFIRMED: table names.
 */
extern unsigned int D_kernel_bss_97DF0[2];
int DIntr(void);
int EIntr(void);

void Sg2SlotSetKeyOnBit(int core, unsigned int bits) {
    int intr = DIntr();

    D_kernel_bss_97DF0[core] |= bits;
    if (intr) {
        EIntr();
    }
}
