/* KERNEL.XFF @ 0x00BF10 (12 B) - iosClearTransCurrentMatrix
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosClearTransCurrentMatrix(void) {
    __asm__ __volatile__(
        "vmove.xyzw $vf4, $vf0\n");
}
