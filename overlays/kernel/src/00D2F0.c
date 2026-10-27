/* KERNEL.XFF @ 0x00D2F0 (68 B) - iosGetScaleMatrixV
 * Evidence: the identity matrix at .data+0x3C0 is copied with a volatile asm (lq/sq pairs through $t1,$t0,$a3,$a2, descending), the same sequence as iosCopyMatrix inlined; then the compiler stores v[0], v[1], v[2] to m[0], m[5], m[10] (strict load/store pairs because m and v may alias).
 */
extern float D_kernel_data_03C0[16];

void iosGetScaleMatrixV(float *m, float *v) {
    __asm__ __volatile__(
        "lq $9, 0x30(%1)\n"
        "sq $9, 0x30(%0)\n"
        "lq $8, 0x20(%1)\n"
        "sq $8, 0x20(%0)\n"
        "lq $7, 0x10(%1)\n"
        "sq $7, 0x10(%0)\n"
        "lq $6, 0x0(%1)\n"
        "sq $6, 0x0(%0)\n" : : "r"(m), "r"(D_kernel_data_03C0) : "$6", "$7", "$8", "$9", "memory");
    m[0] = v[0];
    m[5] = v[1];
    m[10] = v[2];
}
