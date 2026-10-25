/* KERNEL.XFF @ 0x029390 (48 B) - Sg2SlotFree
 * Evidence: clears word +4 of the 0xE0-byte slot [i] at .bss+0x97E30 when it is positive (bgtzl slot store).
 */
struct Sg2Slot {
    unsigned int flags;
    int owner;
    int unk8;
    int cls;
    char pad[0xE0 - 0x10];
};
extern struct Sg2Slot D_kernel_bss_97E30[48];

void Sg2SlotFree(int i) {
    if (D_kernel_bss_97E30[i].owner > 0) {
        D_kernel_bss_97E30[i].owner = 0;
    }
}
