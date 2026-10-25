/* KERNEL.XFF @ 0x00D380 (96 B) - iosRotTransCurrentMatrix
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosRotTransCurrentMatrix(void *a0, void *a1, void *a2, void *a3) {
    __asm__ __volatile__(
        "lqc2 $vf8, 0x0($5)\n"
        "vmulax.xyzw ACC, $vf1, $vf8x\n"
        "vmadday.xyzw ACC, $vf2, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf3, $vf8z\n"
        "vmaddw.xyzw $vf10, $vf4, $vf8w\n"
        "vdiv Q, $vf0w, $vf10w\n"
        "vwaitq\n"
        "vmulq.xyz $vf10, $vf10, Q\n"
        "vftoi4.xyz $vf10, $vf10\n"
        "vsub.xy $vf14, $vf10, $vf11\n"
        "vsub.xy $vf15, $vf12, $vf11\n"
        "vsub.zw $vf14, $vf14, $vf14\n"
        "vsub.zw $vf15, $vf15, $vf15\n"
        "vopmula.xyz ACC, $vf14, $vf15\n"
        "vopmsub.xyz $vf16, $vf15, $vf14\n"
        "vmr32.y $vf16, $vf16\n"
        "vmr32.x $vf16, $vf16\n"
        "sqc2 $vf10, 0x0($4)\n"
        "qmfc2.ni $7, $vf16\n"
        "mtc1 $7, $f0\n"
        "vmove.xy $vf12, $vf11\n"
        "vmove.xy $vf11, $vf10\n");
}
