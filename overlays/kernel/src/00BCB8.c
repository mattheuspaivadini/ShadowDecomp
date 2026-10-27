/* KERNEL.XFF @ 0x00BCB8 (24 B) - iosPopCurrentMatrix
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosPopCurrentMatrix(void) {
    __asm__ __volatile__(
        "vlqd.xyzw $vf4, (--$vi15)\n"
        "vlqd.xyzw $vf3, (--$vi15)\n"
        "vlqd.xyzw $vf2, (--$vi15)\n"
        "vlqd.xyzw $vf1, (--$vi15)\n");
}
