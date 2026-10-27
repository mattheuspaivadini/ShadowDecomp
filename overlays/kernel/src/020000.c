/* KERNEL.XFF @ 0x020000 (112 B) - Sg2ExStAdpcmSlotFree
 * Evidence: Sg2SlotFree(i) for every positive entry of the 48-word table at .bss+0x7F600, clearing it and counting; returns the count.
 */
extern int D_kernel_bss_7F600[48];
void Sg2SlotFree(int i);

int Sg2ExStAdpcmSlotFree(void) {
    int n = 0;
    int i;

    for (i = 0; i < 48; i++) {
        if (D_kernel_bss_7F600[i] > 0) {
            Sg2SlotFree(i);
            n++;
            D_kernel_bss_7F600[i] = 0;
        }
    }
    return n;
}
