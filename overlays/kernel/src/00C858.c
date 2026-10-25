/* KERNEL.XFF @ 0x00C858 (72 B) - iosTransposeMatrix
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosTransposeMatrix(void *a0, void *a1) {
    __asm__ __volatile__(
        "lq $8, 0x0($5)\n"
        "lq $9, 0x10($5)\n"
        "lq $10, 0x20($5)\n"
        "lq $11, 0x30($5)\n"
        "pextlw $12, $9, $8\n"
        "pextuw $13, $9, $8\n"
        "pextlw $14, $11, $10\n"
        "pextuw $15, $11, $10\n"
        "pcpyld $8, $14, $12\n"
        "pcpyud $9, $12, $14\n"
        "pcpyld $10, $15, $13\n"
        "pcpyud $11, $13, $15\n"
        "sq $8, 0x0($4)\n"
        "sq $9, 0x10($4)\n"
        "sq $10, 0x20($4)\n"
        "sq $11, 0x30($4)\n");
}
