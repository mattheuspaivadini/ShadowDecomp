/* KERNEL.XFF @ 0x00C438 (44 B) - iosRotTransPersCurrentMatrix
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosRotTransPersCurrentMatrix(void *a0, void *a1) {
    __asm__ __volatile__(
        "lqc2 $vf8, 0x0($5)\n"
        "vmulax.xyzw ACC, $vf1, $vf8x\n"
        "vmadday.xyzw ACC, $vf2, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf3, $vf8z\n"
        "vmaddw.xyzw $vf10, $vf4, $vf8w\n"
        "vdiv Q, $vf0w, $vf10w\n"
        "vwaitq\n"
        "vmulq.xyz $vf10, $vf10, Q\n"
        "sqc2 $vf10, 0x0($4)\n");
}
