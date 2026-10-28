/* KERNEL.XFF @ 0x02A6F8 (324 B) - Sg2SlotVabKeyOffGroup
 * Evidence: under DIntr/EIntr (EIntr tail call): every used slot (bit 0) of the 48 Sg2 slots whose +0x10 equals vab and +0x1C equals group gets the static .text+0x29D38(i, 0, 8), its key-off bit ORed into .bss+0x97DF8[i >= 24] and +0x1C = -1 (sibling of Sg2SlotModKeyOff). UNCONFIRMED: names.
 */
struct Sg2Slot {
    unsigned int flags;
    char pad4[0xC];
    int vab;
    char pad14[8];
    int group;
    char pad20[0xE0 - 0x20];
};
extern struct Sg2Slot D_kernel_bss_97E30[48];
extern unsigned int D_kernel_bss_97DF8[2];
int DIntr(void);
int EIntr(void);
void func_029D38(int i, int a, int b);

void Sg2SlotVabKeyOffGroup(int vab, int group) {
    int intr = DIntr();
    int i;

    for (i = 0; i < 48; i++) {
        if ((D_kernel_bss_97E30[i].flags & 1) && D_kernel_bss_97E30[i].vab == vab && D_kernel_bss_97E30[i].group == group) {
            func_029D38(i, 0, 8);
            D_kernel_bss_97DF8[i >= 24] |= i < 24 ? 1 << i : 1 << (i - 24);
            D_kernel_bss_97E30[i].group = -1;
        }
    }
    if (intr) {
        EIntr();
    }
}
