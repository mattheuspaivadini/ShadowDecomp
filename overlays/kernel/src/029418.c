/* KERNEL.XFF @ 0x029418 (72 B) - Sg2SlotFindLoop
 * Evidence: writes the index of every slot with bit 2 set to out[] and returns the count.
 */
struct Sg2Slot {
    unsigned int flags;
    int owner;
    int unk8;
    int cls;
    char pad[0xE0 - 0x10];
};
extern struct Sg2Slot D_kernel_bss_97E30[48];

int Sg2SlotFindLoop(int *out) {
    int n = 0;
    int i;

    for (i = 0; i < 48; i++) {
        if (D_kernel_bss_97E30[i].flags & 4) {
            *out++ = i;
            n++;
        }
    }
    return n;
}
