/* KERNEL.XFF @ 0x00CC90 (116 B) - iosTransMatrixF
 * Evidence: a stack vector {x, y, z, 1}; the source matrix is copied with the volatile lq/sq asm (iosCopyMatrix sequence), then a volatile VU0 asm transforms the vector by the source rows into d[12..15]. The vector address goes through a pointer variable (daddu v0,sp,zero).
 */
static __inline__ void copyMatrix(void *d, void *s) {
    __asm__ __volatile__(
        "lq $9, 0x30(%1)\n"
        "sq $9, 0x30(%0)\n"
        "lq $8, 0x20(%1)\n"
        "sq $8, 0x20(%0)\n"
        "lq $7, 0x10(%1)\n"
        "sq $7, 0x10(%0)\n"
        "lq $6, 0x0(%1)\n"
        "sq $6, 0x0(%0)\n" : : "r"(d), "r"(s) : "$6", "$7", "$8", "$9", "memory");
}

void iosTransMatrixF(float *d, float *s, float x, float y, float z) {
    float v[4] __attribute__((aligned(16)));
    float *pv = v;

    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = 1.0f;
    copyMatrix(d, s);
    __asm__ __volatile__(
        "lqc2 $vf8, 0x0(%1)\n"
        "lqc2 $vf14, 0x0(%2)\n"
        "lqc2 $vf15, 0x10(%2)\n"
        "lqc2 $vf16, 0x20(%2)\n"
        "lqc2 $vf17, 0x30(%2)\n"
        "vmulax.xyzw ACC, $vf14, $vf8x\n"
        "vmadday.xyzw ACC, $vf15, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf16, $vf8z\n"
        "vmaddw.xyzw $vf10, $vf17, $vf8w\n"
        "sqc2 $vf10, 0x0(%0)\n" : : "r"(d + 12), "r"(pv), "r"(s) : "memory");
}
