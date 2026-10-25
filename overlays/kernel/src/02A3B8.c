/* KERNEL.XFF @ 0x02A3B8 (32 B) - Sg2SlotGetVol
 * Evidence: returns word +0x48 (volume) of the 0xE0-byte slot [i] at .bss+0x97E30.
 */
struct Sg2Slot {
    char pad[0x48];
    int vol;
    char pad4C[8];
    int pan;
    char pad58[0xE0 - 0x58];
};
extern struct Sg2Slot D_kernel_bss_97E30[48];

int Sg2SlotGetVol(int i) {
    return D_kernel_bss_97E30[i].vol;
}
