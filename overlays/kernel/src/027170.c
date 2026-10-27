/* KERNEL.XFF @ 0x027170 (28 B) - Sg2SlotGetSlotClassIdx
 * Evidence: returns .bss+0x97E24 and post-increments it.
 */
extern int D_kernel_bss_97E24;

int Sg2SlotGetSlotClassIdx(void) {
    return D_kernel_bss_97E24++;
}
