/* KERNEL.XFF @ 0x012260 (32 B) - iosScaleColorToONE
 * Evidence: volatile VU0 asm: col * (.rodata+0x1110). Same vf5/vf6 mismatch as
 * iosScaleColorTo255.
 */
extern float D_kernel_rodata_1110[4];
void iosScaleColorToONE(float *d, float *s) {
    __asm__ __volatile__(
        "lqc2 $vf4, 0x0(%1)
"
        "lqc2 $vf5, 0x0(%2)
"
        "vmul.xyzw $vf5, $vf4, $vf5
"
        "sqc2 $vf6, 0x0(%0)
" : : "r"(d), "r"(s), "r"(D_kernel_rodata_1110) : "memory");
}
