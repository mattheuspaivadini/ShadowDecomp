/* KERNEL.XFF @ 0x0298D8 (128 B) - Sg2SlotSetMute
 * Evidence: sets or clears flag 0x8000 (mute) and then sets 0x1000 (volume update). Voice slots are the 48 0xE0-byte records at .bss+0x97E30. UNCONFIRMED: field names.
 */
struct Sg2Slot {
    unsigned int flags;
    int owner;
    int age;
    int cls;
    int vab;
    int ch;
    int unk18;
    int unk1C;
    int unk20;
    int note;
    int base;
    char pad2C[0x34];
    int ssa;
    char pad64[0xE0 - 0x64];
};
extern struct Sg2Slot D_kernel_bss_97E30[48];

void Sg2SlotSetMute(int i, int on) {
    if (on) {
        D_kernel_bss_97E30[i].flags |= 0x8000;
    } else {
        D_kernel_bss_97E30[i].flags &= ~0x8000;
    }
    D_kernel_bss_97E30[i].flags |= 0x1000;
}
