/* KERNEL.XFF @ 0x0005C8 (84 B) - iosCdStSectorAlignSkip
 * Evidence: rem = (int)(pos % 2048) on the signed 64-bit stream position at .bss+0x8050 (slti/movn rounding toward zero, dsra/dsll 11); when rem != 0 the position is advanced by the zero-extended (0x800 - rem) to the next sector boundary.
 */
extern long D_kernel_bss_8050;

void iosCdStSectorAlignSkip(void) {
    int rem = D_kernel_bss_8050 % 2048;

    if (rem != 0) {
        D_kernel_bss_8050 += (unsigned int)(0x800 - rem);
    }
}
