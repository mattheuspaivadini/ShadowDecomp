/* KERNEL.XFF @ 0x00C268 (140 B) - iosScaleCurrentMatrix
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosScaleCurrentMatrix(void *a0, void *a1, void *a2, void *a3, float f12, float f13, float f14) {
    __asm__ __volatile__(
        "vmove.xyzw $vf17, $vf0\n"
        "vmr32.xyzw $vf16, $vf17\n"
        "vmr32.xyzw $vf15, $vf16\n"
        "vmr32.xyzw $vf14, $vf15\n"
        "mfc1 $6, $f12\n"
        "mfc1 $7, $f13\n"
        "mfc1 $8, $f14\n"
        "qmtc2.ni $6, $vf5\n"
        "qmtc2.ni $7, $vf6\n"
        "qmtc2.ni $8, $vf7\n"
        "vaddx.x $vf14, $vf0, $vf5x\n"
        "vaddx.y $vf15, $vf0, $vf6x\n"
        "vaddx.z $vf16, $vf0, $vf7x\n"
        "vmulax.xyzw ACC, $vf1, $vf14x\n"
        "vmadday.xyzw ACC, $vf2, $vf14y\n"
        "vmaddaz.xyzw ACC, $vf3, $vf14z\n"
        "vmaddw.xyzw $vf14, $vf4, $vf14w\n"
        "vmulax.xyzw ACC, $vf1, $vf15x\n"
        "vmadday.xyzw ACC, $vf2, $vf15y\n"
        "vmaddaz.xyzw ACC, $vf3, $vf15z\n"
        "vmaddw.xyzw $vf15, $vf4, $vf15w\n"
        "vmulax.xyzw ACC, $vf1, $vf16x\n"
        "vmadday.xyzw ACC, $vf2, $vf16y\n"
        "vmaddaz.xyzw ACC, $vf3, $vf16z\n"
        "vmaddw.xyzw $vf16, $vf4, $vf16w\n"
        "vmulax.xyzw ACC, $vf1, $vf17x\n"
        "vmadday.xyzw ACC, $vf2, $vf17y\n"
        "vmaddaz.xyzw ACC, $vf3, $vf17z\n"
        "vmaddw.xyzw $vf17, $vf4, $vf17w\n"
        "vmove.xyzw $vf1, $vf14\n"
        "vmove.xyzw $vf2, $vf15\n"
        "vmove.xyzw $vf3, $vf16\n"
        "vmove.xyzw $vf4, $vf17\n");
}
