/* KERNEL.XFF @ 0x029510 (104 B) - Sg2SlotFindVabChNote
 * Evidence: keys vab (+0x10), ch (+0x14), note (+0x24): writes the index of every active slot (bit 0) matching all keys to out[] and returns the count. Voice slots are the 48 0xE0-byte records at .bss+0x97E30. UNCONFIRMED: field names.
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

int Sg2SlotFindVabChNote(int *out, int k, int ch, int note) {
    struct Sg2Slot *s = D_kernel_bss_97E30;
    int n = 0;
    int i;

    for (i = 0; i < 48; i++, s++) {
        if ((s->flags & 1) && s->vab == k && s->ch == ch
            && s->note == note) {
            *out++ = i;
            n++;
        }
    }
    return n;
}
