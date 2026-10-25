/* KERNEL.XFF @ 0x00D0C0 (108 B) - iosRotMatrixY
 * Evidence: Y rotation: m[8] = s, m[0] = m[10] = c, m[2] = -s; iosGetAlignSinCosf(sc, angle) into a stack pair, the identity at .data+0x3C0 copied by the volatile lq/sq asm (iosCopyMatrix sequence), then the four rotation terms (the second written term is emitted third by the scheduler).
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
extern float D_kernel_data_03C0[16];
void iosGetAlignSinCosf(float *sc, float angle);

void iosRotMatrixY(float *m, float angle) {
    float sc[2];

    iosGetAlignSinCosf(sc, angle);
    copyMatrix(m, D_kernel_data_03C0);
    m[8] = sc[0];
    m[0] = sc[1];
    m[10] = sc[1];
    m[2] = -sc[0];
}
