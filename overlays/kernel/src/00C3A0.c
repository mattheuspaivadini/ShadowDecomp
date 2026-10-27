/* KERNEL.XFF @ 0x00C3A0 (88 B) - iosMulCurrentMatrixL
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosMulCurrentMatrixL(void *a0) {
    __asm__ __volatile__(
        "lqc2 $vf14, 0x0($4)\n"
        "lqc2 $vf15, 0x10($4)\n"
        "lqc2 $vf16, 0x20($4)\n"
        "lqc2 $vf17, 0x30($4)\n"
        "vmulax.xyzw ACC, $vf14, $vf1x\n"
        "vmadday.xyzw ACC, $vf15, $vf1y\n"
        "vmaddaz.xyzw ACC, $vf16, $vf1z\n"
        "vmaddw.xyzw $vf1, $vf17, $vf1w\n"
        "vmulax.xyzw ACC, $vf14, $vf2x\n"
        "vmadday.xyzw ACC, $vf15, $vf2y\n"
        "vmaddaz.xyzw ACC, $vf16, $vf2z\n"
        "vmaddw.xyzw $vf2, $vf17, $vf2w\n"
        "vmulax.xyzw ACC, $vf14, $vf3x\n"
        "vmadday.xyzw ACC, $vf15, $vf3y\n"
        "vmaddaz.xyzw ACC, $vf16, $vf3z\n"
        "vmaddw.xyzw $vf3, $vf17, $vf3w\n"
        "vmulax.xyzw ACC, $vf14, $vf4x\n"
        "vmadday.xyzw ACC, $vf15, $vf4y\n"
        "vmaddaz.xyzw ACC, $vf16, $vf4z\n"
        "vmaddw.xyzw $vf4, $vf17, $vf4w\n");
}
