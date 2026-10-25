/* KERNEL.XFF @ 0x00C7B0 (40 B) - iosCopyMatrix
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosCopyMatrix(void *a0, void *a1, void *a2, void *a3) {
    __asm__ __volatile__(
        "lq $9, 0x30($5)\n"
        "sq $9, 0x30($4)\n"
        "lq $8, 0x20($5)\n"
        "sq $8, 0x20($4)\n"
        "lq $7, 0x10($5)\n"
        "sq $7, 0x10($4)\n"
        "lq $6, 0x0($5)\n"
        "sq $6, 0x0($4)\n");
}
