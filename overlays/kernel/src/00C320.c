/* KERNEL.XFF @ 0x00C320 (24 B) - iosSetCurrentMatrix
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosSetCurrentMatrix(void *a0) {
    __asm__ __volatile__(
        "lqc2 $vf1, 0x0($4)\n"
        "lqc2 $vf2, 0x10($4)\n"
        "lqc2 $vf3, 0x20($4)\n"
        "lqc2 $vf4, 0x30($4)\n");
}
