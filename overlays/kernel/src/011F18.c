/* KERNEL.XFF @ 0x011F18 (48 B) - iosGetReflectVector
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosGetReflectVector(void *a0, void *a1, void *a2) {
    __asm__ __volatile__(
        "lqc2 $vf4, 0x0($5)\n"
        "lqc2 $vf5, 0x0($6)\n"
        "vmul.xyz $vf7, $vf4, $vf5\n"
        "vaddy.x $vf7, $vf7, $vf7y\n"
        "vaddz.x $vf7, $vf7, $vf7z\n"
        "vadd.xyzw $vf6, $vf0, $vf0\n"
        "vmulx.xyz $vf5, $vf5, $vf7x\n"
        "vmulw.xyz $vf5, $vf5, $vf6w\n"
        "vsub.xyz $vf4, $vf4, $vf5\n"
        "sqc2 $vf4, 0x0($4)\n");
}
