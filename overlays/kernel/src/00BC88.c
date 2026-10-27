/* KERNEL.XFF @ 0x00BC88 (24 B) - iosUnitCurrentMatrix
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosUnitCurrentMatrix(void) {
    __asm__ __volatile__(
        "vmove.xyzw $vf4, $vf0\n"
        "vmr32.xyzw $vf3, $vf4\n"
        "vmr32.xyzw $vf2, $vf3\n"
        "vmr32.xyzw $vf1, $vf2\n");
}
