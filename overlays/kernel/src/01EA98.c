/* KERNEL.XFF @ 0x01EA98 (44 B) - setSoundMode
 * Evidence: mode = arg ? 1 : 2 (movz), stored to .data+0xA20 and passed to sibling Sg2SlotSetOutputMode.
 */
extern int D_kernel_data_0A20;
void Sg2SlotSetOutputMode(int mode);

void setSoundMode(int stereo) {
    int mode = stereo ? 1 : 2;

    D_kernel_data_0A20 = mode;
    Sg2SlotSetOutputMode(mode);
}
