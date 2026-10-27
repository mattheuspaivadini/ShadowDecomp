/* KERNEL.XFF @ 0x00BCA0 (24 B) - iosPushCurrentMatrix
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosPushCurrentMatrix(void) {
    __asm__ __volatile__(
        "vsqi.xyzw $vf1, ($vi15++)\n"
        "vsqi.xyzw $vf2, ($vi15++)\n"
        "vsqi.xyzw $vf3, ($vi15++)\n"
        "vsqi.xyzw $vf4, ($vi15++)\n");
}
