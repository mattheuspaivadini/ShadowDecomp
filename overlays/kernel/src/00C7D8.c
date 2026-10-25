/* KERNEL.XFF @ 0x00C7D8 (44 B) - iosApplyRotMatrix
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosApplyRotMatrix(void *a0, void *a1, void *a2) {
    __asm__ __volatile__(
        "lqc2 $vf8, 0x0($6)\n"
        "lqc2 $vf14, 0x0($5)\n"
        "lqc2 $vf15, 0x10($5)\n"
        "lqc2 $vf16, 0x20($5)\n"
        "vmulax.xyzw ACC, $vf14, $vf8x\n"
        "vmadday.xyzw ACC, $vf15, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf16, $vf8z\n"
        "vmaddw.xyzw $vf10, $vf0, $vf8w\n"
        "sqc2 $vf10, 0x0($4)\n");
}
