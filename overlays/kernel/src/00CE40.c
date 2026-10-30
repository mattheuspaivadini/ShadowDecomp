/* KERNEL.XFF @ 0x00CE40 (260 B) - iosMulRotMatrixYInt16
 * Evidence: byte-identical shape to iosMulRotMatrixXInt16 with the Y terms in
 * m[0],m[2],m[8],m[10]; that source order is what reproduces the shipped swc1
 * schedule. UNCONFIRMED: names/types.
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
float iosGetTableCos(short a);
float iosGetTableSin(short a);

void iosMulRotMatrixYInt16(float *d, float *s, short angle) {
    float m[16] __attribute__((aligned(16)));
    float c, sn;

    c = iosGetTableCos(angle);
    sn = iosGetTableSin(angle);
    copyMatrix(m, D_kernel_data_03C0);
    m[0] = c;
    m[2] = -sn;
    m[8] = sn;
    m[10] = c;
    __asm__ __volatile__(
        "lqc2 $vf14, 0x0(%1)\n"
        "lqc2 $vf15, 0x10(%1)\n"
        "lqc2 $vf16, 0x20(%1)\n"
        "lqc2 $vf17, 0x30(%1)\n"
        "lqc2 $vf24, 0x0(%2)\n"
        "lqc2 $vf25, 0x10(%2)\n"
        "lqc2 $vf26, 0x20(%2)\n"
        "lqc2 $vf27, 0x30(%2)\n"
        "vmulax.xyzw ACC, $vf14, $vf24x\n"
        "vmadday.xyzw ACC, $vf15, $vf24y\n"
        "vmaddaz.xyzw ACC, $vf16, $vf24z\n"
        "vmaddw.xyzw $vf24, $vf17, $vf24w\n"
        "vmulax.xyzw ACC, $vf14, $vf25x\n"
        "vmadday.xyzw ACC, $vf15, $vf25y\n"
        "vmaddaz.xyzw ACC, $vf16, $vf25z\n"
        "vmaddw.xyzw $vf25, $vf17, $vf25w\n"
        "vmulax.xyzw ACC, $vf14, $vf26x\n"
        "vmadday.xyzw ACC, $vf15, $vf26y\n"
        "vmaddaz.xyzw ACC, $vf16, $vf26z\n"
        "vmaddw.xyzw $vf26, $vf17, $vf26w\n"
        "vmulax.xyzw ACC, $vf14, $vf27x\n"
        "vmadday.xyzw ACC, $vf15, $vf27y\n"
        "vmaddaz.xyzw ACC, $vf16, $vf27z\n"
        "vmaddw.xyzw $vf27, $vf17, $vf27w\n"
        "sqc2 $vf24, 0x0(%0)\n"
        "sqc2 $vf25, 0x10(%0)\n"
        "sqc2 $vf26, 0x20(%0)\n"
        "sqc2 $vf27, 0x30(%0)\n" : : "r"(d), "r"(s), "r"(m) : "memory");
}
