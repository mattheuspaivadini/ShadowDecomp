/* KERNEL.XFF @ 0x00BF20 (164 B) - iosGetRotXVector
 * Evidence: iosGetSinCosf(&sc, angle) fills a 2-float pair; the identity is
 * built in vf14..vf17 (vmove + 3 x vmr32), the pair is read with lwc1/mfc1 into
 * hard $8/$9 and the X terms patched with vaddx/vsubx; the matrix is spilled
 * with 4 x sqc2 and `v x m` is a second volatile asm ending in sqc2 to *d.
 * The sin/cos pair is passed as an "m" operand so GCC prints 0x40($sp)
 * directly (an "r" operand would materialise &sc in a saved register).
 * UNCONFIRMED: parameter names.
 */
void iosGetSinCosf(float *sc, float angle);

void iosGetRotXVector(float *d, float *v, float angle) {
    float m[16] __attribute__((aligned(16)));
    float sc[2];

    iosGetSinCosf(sc, angle);
    __asm__ __volatile__(
        "vmove.xyzw $vf17, $vf0\n"
        "vmr32.xyzw $vf16, $vf17\n"
        "vmr32.xyzw $vf15, $vf16\n"
        "vmr32.xyzw $vf14, $vf15\n");
    __asm__ __volatile__(
        "lwc1 $f1, %0\n"
        "lwc1 $f0, %1\n"
        "mfc1 $8, $f1\n"
        "mfc1 $9, $f0\n"
        "qmtc2.ni $8, $vf5\n"
        "qmtc2.ni $9, $vf6\n"
        "vaddx.y $vf15, $vf0, $vf5x\n"
        "vsubx.y $vf16, $vf0, $vf6x\n"
        "vaddx.z $vf15, $vf0, $vf6x\n"
        "vaddx.z $vf16, $vf0, $vf5x\n"
        "sqc2 $vf14, 0x0(%2)\n"
        "sqc2 $vf15, 0x10(%2)\n"
        "sqc2 $vf16, 0x20(%2)\n"
        "sqc2 $vf17, 0x30(%2)\n" : : "m"(sc[0]), "m"(sc[1]), "r"(m)
        : "$8", "$9", "$f0", "$f1", "memory");
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
        "sqc2 $vf10, 0x0(%0)\n" : : "r"(d), "r"(v), "r"(m) : "memory");
}
