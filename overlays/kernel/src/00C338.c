/* KERNEL.XFF @ 0x00C338 (104 B) - iosMulCurrentMatrixR
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosMulCurrentMatrixR(void *a0) {
    __asm__ __volatile__(
        "lqc2 $vf14, 0x0($4)\n"
        "lqc2 $vf15, 0x10($4)\n"
        "lqc2 $vf16, 0x20($4)\n"
        "lqc2 $vf17, 0x30($4)\n"
        "vmulax.xyzw ACC, $vf1, $vf14x\n"
        "vmadday.xyzw ACC, $vf2, $vf14y\n"
        "vmaddaz.xyzw ACC, $vf3, $vf14z\n"
        "vmaddw.xyzw $vf14, $vf4, $vf14w\n"
        "vmulax.xyzw ACC, $vf1, $vf15x\n"
        "vmadday.xyzw ACC, $vf2, $vf15y\n"
        "vmaddaz.xyzw ACC, $vf3, $vf15z\n"
        "vmaddw.xyzw $vf15, $vf4, $vf15w\n"
        "vmulax.xyzw ACC, $vf1, $vf16x\n"
        "vmadday.xyzw ACC, $vf2, $vf16y\n"
        "vmaddaz.xyzw ACC, $vf3, $vf16z\n"
        "vmaddw.xyzw $vf16, $vf4, $vf16w\n"
        "vmulax.xyzw ACC, $vf1, $vf17x\n"
        "vmadday.xyzw ACC, $vf2, $vf17y\n"
        "vmaddaz.xyzw ACC, $vf3, $vf17z\n"
        "vmaddw.xyzw $vf17, $vf4, $vf17w\n"
        "vmove.xyzw $vf1, $vf14\n"
        "vmove.xyzw $vf2, $vf15\n"
        "vmove.xyzw $vf3, $vf16\n"
        "vmove.xyzw $vf4, $vf17\n");
}
