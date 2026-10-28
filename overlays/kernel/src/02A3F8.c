/* KERNEL.XFF @ 0x02A3F8 (224 B) - Sg2SlotSetDumperOff
 * Evidence: under DIntr/EIntr (EIntr tail call): every slot (0xE0 bytes at .bss+0x97E30) with flags bit 0 and bit 3 set, class +0xC == cls and +0x14 == id gets bit 3 cleared and its bit ORed into the per-core key-off word (.bss+0x97DF8 [i >= 24], bit i mod 24). UNCONFIRMED: field names.
 */
struct Sg2Slot {
    unsigned int flags;
    int owner;
    int unk8;
    int cls;
    int unk10;
    int id;
    char pad18[0xE0 - 0x18];
};
extern struct Sg2Slot D_kernel_bss_97E30[48];
extern unsigned int D_kernel_bss_97DF8[2];
int DIntr(void);
int EIntr(void);

void Sg2SlotSetDumperOff(int cls, int id) {
    int intr = DIntr();
    int i;

    for (i = 0; i < 48; i++) {
        if ((D_kernel_bss_97E30[i].flags & 1) && (D_kernel_bss_97E30[i].flags & 8) && D_kernel_bss_97E30[i].cls == cls && D_kernel_bss_97E30[i].id == id) {
            D_kernel_bss_97E30[i].flags &= ~8;
            D_kernel_bss_97DF8[i >= 24] |= i < 24 ? 1 << i : 1 << (i - 24);
        }
    }
    if (intr) {
        EIntr();
    }
}
