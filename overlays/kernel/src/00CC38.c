/* KERNEL.XFF @ 0x00CC38 (88 B) - iosTransMatrix
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
int iosTransMatrix(void *a0, void *a1, void *a2, void *a3) {
    __asm__ __volatile__(
        "daddu $2, $6, $0\n"
        "lq $9, 0x30($5)\n"
        "sq $9, 0x30($4)\n"
        "lq $8, 0x20($5)\n"
        "sq $8, 0x20($4)\n"
        "lq $7, 0x10($5)\n"
        "sq $7, 0x10($4)\n"
        "lq $6, 0x0($5)\n"
        "sq $6, 0x0($4)\n"
        "addiu $4, $4, 0x30\n"
        "lqc2 $vf8, 0x0($2)\n"
        "lqc2 $vf14, 0x0($5)\n"
        "lqc2 $vf15, 0x10($5)\n"
        "lqc2 $vf16, 0x20($5)\n"
        "lqc2 $vf17, 0x30($5)\n"
        "vmulax.xyzw ACC, $vf14, $vf8x\n"
        "vmadday.xyzw ACC, $vf15, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf16, $vf8z\n"
        "vmaddw.xyzw $vf10, $vf17, $vf8w\n"
        "sqc2 $vf10, 0x0($4)\n");
}
