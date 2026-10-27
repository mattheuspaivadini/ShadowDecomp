/* KERNEL.XFF @ 0x00D350 (20 B) - iosGetXDirXYZFromMatrix
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosGetXDirXYZFromMatrix(void *a0, void *a1) {
    __asm__ __volatile__(
        "lqc2 $vf4, 0x0($5)\n"
        "vsub.w $vf4, $vf4, $vf4\n"
        "sqc2 $vf4, 0x0($4)\n");
}
