/* KERNEL.XFF @ 0x00BC68 (28 B) - iosInitCurrentMatrix
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosInitCurrentMatrix(void) {
    __asm__ __volatile__(
        "vmove.xyzw $vf4, $vf0\n"
        "vmr32.xyzw $vf3, $vf4\n"
        "vmr32.xyzw $vf2, $vf3\n"
        "vmr32.xyzw $vf1, $vf2\n"
        "viaddi $vi15, $vi0, 0x0\n");
}
