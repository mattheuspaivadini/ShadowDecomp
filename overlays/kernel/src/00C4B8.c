/* KERNEL.XFF @ 0x00C4B8 (48 B) - iosTransposeRotationCurrentMatrix
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosTransposeRotationCurrentMatrix(void) {
    __asm__ __volatile__(
        "vsub.xyzw $vf5, $vf0, $vf0\n"
        "vaddx.y $vf14, $vf5, $vf2x\n"
        "vaddx.z $vf14, $vf5, $vf3x\n"
        "vaddy.x $vf15, $vf5, $vf1y\n"
        "vaddy.z $vf15, $vf5, $vf3y\n"
        "vaddz.x $vf16, $vf5, $vf1z\n"
        "vaddz.y $vf16, $vf5, $vf2z\n"
        "vmove.yz $vf1, $vf14\n"
        "vmove.xz $vf2, $vf15\n"
        "vmove.xy $vf3, $vf16\n");
}
