/* KERNEL.XFF @ 0x02A3D8 (32 B) - Sg2SlotGetPan
 * Evidence: returns word +0x54 (pan) of the 0xE0-byte slot [i] at .bss+0x97E30.
 */
struct Sg2Slot {
    char pad[0x48];
    int vol;
    char pad4C[8];
    int pan;
    char pad58[0xE0 - 0x58];
};
extern struct Sg2Slot D_kernel_bss_97E30[48];

int Sg2SlotGetPan(int i) {
    return D_kernel_bss_97E30[i].pan;
}
