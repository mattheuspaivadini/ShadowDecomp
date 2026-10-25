/* KERNEL.XFF @ 0x00CBC8 (56 B) - iosScaleNormalLightMatrix
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosScaleNormalLightMatrix(void *a0, void *a1, void *a2) {
    __asm__ __volatile__(
        "lqc2 $vf24, 0x0($5)\n"
        "lqc2 $vf25, 0x10($5)\n"
        "lqc2 $vf26, 0x20($5)\n"
        "lqc2 $vf27, 0x30($5)\n"
        "lqc2 $vf28, 0x0($6)\n"
        "vmulx.xyz $vf24, $vf24, $vf28x\n"
        "vmuly.xyz $vf25, $vf25, $vf28y\n"
        "vmulz.xyz $vf26, $vf26, $vf28z\n"
        "sqc2 $vf24, 0x0($4)\n"
        "sqc2 $vf25, 0x10($4)\n"
        "sqc2 $vf26, 0x20($4)\n"
        "sqc2 $vf27, 0x30($4)\n");
}
