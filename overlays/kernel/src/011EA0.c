/* KERNEL.XFF @ 0x011EA0 (28 B) - iosGetRandomVector
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosGetRandomVector(void *a0) {
    __asm__ __volatile__(
        "vrnext.x $vf5, R\n"
        "vrnext.y $vf5, R\n"
        "vrnext.z $vf5, R\n"
        "vsubw.xyz $vf5, $vf5, $vf0w\n"
        "sqc2 $vf5, 0x0($4)\n");
}
