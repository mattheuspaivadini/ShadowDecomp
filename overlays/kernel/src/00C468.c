/* KERNEL.XFF @ 0x00C468 (76 B) - iosTransposeCurrentMatrix
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosTransposeCurrentMatrix(void) {
    __asm__ __volatile__(
        "vsub.xyzw $vf5, $vf0, $vf0\n"
        "vaddx.y $vf14, $vf5, $vf2x\n"
        "vaddx.z $vf14, $vf5, $vf3x\n"
        "vaddx.w $vf14, $vf5, $vf4x\n"
        "vaddy.x $vf15, $vf5, $vf1y\n"
        "vaddy.z $vf15, $vf5, $vf3y\n"
        "vaddy.w $vf15, $vf5, $vf4y\n"
        "vaddz.x $vf16, $vf5, $vf1z\n"
        "vaddz.y $vf16, $vf5, $vf2z\n"
        "vaddz.w $vf16, $vf5, $vf4z\n"
        "vaddw.x $vf17, $vf5, $vf1w\n"
        "vaddw.y $vf17, $vf5, $vf2w\n"
        "vaddw.z $vf17, $vf5, $vf3w\n"
        "vmove.yzw $vf1, $vf14\n"
        "vmove.xzw $vf2, $vf15\n"
        "vmove.xyw $vf3, $vf16\n"
        "vmove.xyz $vf4, $vf17\n");
}
