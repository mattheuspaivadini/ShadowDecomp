/* KERNEL.XFF @ 0x00C938 (56 B) - iosScaleMatrixV
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosScaleMatrixV(void *a0, void *a1, void *a2) {
    __asm__ __volatile__(
        "lqc2 $vf14, 0x0($5)\n"
        "lqc2 $vf15, 0x10($5)\n"
        "lqc2 $vf16, 0x20($5)\n"
        "lqc2 $vf17, 0x30($5)\n"
        "lqc2 $vf8, 0x0($6)\n"
        "vmulx.xyzw $vf14, $vf14, $vf8x\n"
        "vmuly.xyzw $vf15, $vf15, $vf8y\n"
        "vmulz.xyzw $vf16, $vf16, $vf8z\n"
        "sqc2 $vf14, 0x0($4)\n"
        "sqc2 $vf15, 0x10($4)\n"
        "sqc2 $vf16, 0x20($4)\n"
        "sqc2 $vf17, 0x30($4)\n");
}
