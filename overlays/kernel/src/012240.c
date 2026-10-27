/* KERNEL.XFF @ 0x012240 (32 B) - iosScaleColorTo255
 * Evidence: volatile VU0 asm: col * (.rodata+0x1100). The product lands in vf5
 * but vf6 is stored - a latent bug in the original asm, reproduced as is.
 */
extern float D_kernel_rodata_1100[4];
void iosScaleColorTo255(float *d, float *s) {
    __asm__ __volatile__(
        "lqc2 $vf4, 0x0(%1)
"
        "lqc2 $vf5, 0x0(%2)
"
        "vmul.xyzw $vf5, $vf4, $vf5
"
        "sqc2 $vf6, 0x0(%0)
" : : "r"(d), "r"(s), "r"(D_kernel_rodata_1100) : "memory");
}
