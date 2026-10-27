/* KERNEL.XFF @ 0x0121F0 (56 B) - iosCalcFColorToBrightness
 * Evidence: volatile VU0 asm multiplies the colour by the .rodata weights at
 * +0x10F0 into a 16-byte stack buffer; the compiler sums x+y+z.
 */
extern float D_kernel_rodata_10F0[4];
float iosCalcFColorToBrightness(float *col) {
    float t[4] __attribute__((aligned(16)));

    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%1)\n"
        "lqc2 $vf6, 0x0(%2)\n"
        "vmul.xyzw $vf5, $vf5, $vf6\n"
        "sqc2 $vf5, 0x0(%0)\n" : : "r"(t), "r"(col), "r"(D_kernel_rodata_10F0) : "memory");
    return t[0] + t[1] + t[2];
}
