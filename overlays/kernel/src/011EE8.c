/* KERNEL.XFF @ 0x011EE8 (24 B) - iosGetRandomVector0
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosGetRandomVector0(void *a0) {
    __asm__ __volatile__(
        "vrnext.xyz $vf5, R\n"
        "vsubw.xyz $vf5, $vf5, $vf0w\n"
        "vrxor R, $vf5x\n"
        "sqc2 $vf5, 0x0($4)\n");
}
