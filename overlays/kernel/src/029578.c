/* KERNEL.XFF @ 0x029578 (116 B) - Sg2SlotFindVabChSsaBaseNote
 * Evidence: keys vab, ch, ssa (+0x60), base note (+0x28): writes the index of every active slot (bit 0) matching all keys to out[] and returns the count. Voice slots are the 48 0xE0-byte records at .bss+0x97E30. UNCONFIRMED: field names.
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

int Sg2SlotFindVabChSsaBaseNote(int *out, int k, int ch, int ssa, int base) {
    int n = 0;
    int i;

    for (i = 0; i < 48; i++) {
        if ((D_kernel_bss_97E30[i].flags & 1) && D_kernel_bss_97E30[i].vab == k && D_kernel_bss_97E30[i].ch == ch
            && D_kernel_bss_97E30[i].ssa == ssa && D_kernel_bss_97E30[i].base == base) {
            *out++ = i;
            n++;
        }
    }
    return n;
}
