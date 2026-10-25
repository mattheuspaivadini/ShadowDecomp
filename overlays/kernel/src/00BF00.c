/* KERNEL.XFF @ 0x00BF00 (16 B) - iosSetTransCurrentMatrix
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosSetTransCurrentMatrix(void *a0) {
    __asm__ __volatile__(
        "lqc2 $vf8, 0x0($4)\n"
        "vmove.xyzw $vf4, $vf8\n");
}
