/* KERNEL.XFF @ 0x02A4D8 (268 B) - Sg2SlotModKeyOff
 * Evidence: under DIntr/EIntr (EIntr tail call): every used slot (bit 0) whose class (+0xC), +0x14 and +0x24 equal (cls, id, sub) gets bit 3 cleared and its key-off bit ORed into .bss+0x97DF8 [i >= 24] (bit i mod 24); the three fields are read through the owner sub-record at +4. UNCONFIRMED: field names.
 */
struct Sg2SlotOwner {
    int owner;
    int unk8;
    int cls;
    int unk10;
    int id;
    char pad18[0x24 - 0x18];
    int sub;
};
struct Sg2Slot {
    unsigned int flags;
    struct Sg2SlotOwner o;
    char pad28[0xE0 - 0x28];
};
extern struct Sg2Slot D_kernel_bss_97E30[48];
extern unsigned int D_kernel_bss_97DF8[2];
int DIntr(void);
int EIntr(void);

void Sg2SlotModKeyOff(int cls, int id, int sub) {
    int intr = DIntr();
    int i;

    for (i = 0; i < 48; i++) {
        if ((D_kernel_bss_97E30[i].flags & 1) && D_kernel_bss_97E30[i].o.cls == cls && D_kernel_bss_97E30[i].o.id == id && D_kernel_bss_97E30[i].o.sub == sub) {
            D_kernel_bss_97E30[i].flags &= ~8;
            D_kernel_bss_97DF8[i >= 24] |= i < 24 ? 1 << i : 1 << (i - 24);
        }
    }
    if (intr) {
        EIntr();
    }
}
