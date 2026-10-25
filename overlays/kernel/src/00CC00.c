/* KERNEL.XFF @ 0x00CC00 (52 B) - iosMakeLightColorMatrix
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
int iosMakeLightColorMatrix(void *a0, void *a1, void *a2, void *a3) {
    __asm__ __volatile__(
        "daddu $10, $6, $0\n"
        "daddu $3, $7, $0\n"
        "daddu $2, $8, $0\n"
        "lq $6, 0x0($5)\n"
        "lq $7, 0x0($10)\n"
        "lq $8, 0x0($3)\n"
        "lq $9, 0x0($2)\n"
        "sq $6, 0x0($4)\n"
        "sq $7, 0x10($4)\n"
        "sq $8, 0x20($4)\n"
        "sq $9, 0x30($4)\n");
}
