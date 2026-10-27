/* KERNEL.XFF @ 0x011D80 (20 B) - iosFTOI0Vector
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosFTOI0Vector(void *a0, void *a1) {
    __asm__ __volatile__(
        "lqc2 $vf5, 0x0($5)\n"
        "vftoi0.xyzw $vf6, $vf5\n"
        "sqc2 $vf6, 0x0($4)\n");
}
