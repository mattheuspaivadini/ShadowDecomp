/* KERNEL.XFF @ 0x011EC0 (36 B) - iosGetDRandomVector
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosGetDRandomVector(void *a0) {
    __asm__ __volatile__(
        "vrnext.x $vf5, R\n"
        "vrnext.y $vf5, R\n"
        "vrnext.z $vf5, R\n"
        "vsubw.xyz $vf5, $vf5, $vf0w\n"
        "vadd.xyz $vf5, $vf5, $vf5\n"
        "vsubw.xyz $vf5, $vf5, $vf0w\n"
        "sqc2 $vf5, 0x0($4)\n");
}
