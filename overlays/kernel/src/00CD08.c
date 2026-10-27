/* KERNEL.XFF @ 0x00CD08 (48 B) - iosScaleMatrix
 * Evidence: a volatile asm writes the VU0 identity matrix (vmove/vmr32 into
 * vf14..vf17, four sqc2 through the matrix pointer), then the compiler stores
 * the three scale factors ($f12/$f13/$f14) to m[0], m[5], m[10].
 */
void iosScaleMatrix(float *m, float sx, float sy, float sz) {
    __asm__ __volatile__(
        "vmove.xyzw $vf17, $vf0\n"
        "vmr32.xyzw $vf16, $vf17\n"
        "vmr32.xyzw $vf15, $vf16\n"
        "vmr32.xyzw $vf14, $vf15\n"
        "sqc2 $vf14, 0x0(%0)\n"
        "sqc2 $vf15, 0x10(%0)\n"
        "sqc2 $vf16, 0x20(%0)\n"
        "sqc2 $vf17, 0x30(%0)\n" : : "r"(m) : "memory");
    m[0] = sx;
    m[5] = sy;
    m[10] = sz;
}
