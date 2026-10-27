/* KERNEL.XFF @ 0x00C118 (164 B) - iosRotCurrentMatrixY
 * Evidence: Y rotation terms (vf14.x/z, vf16.x/z). iosGetSinCosf(sc, angle) into a stack pair; a volatile asm builds the identity in vf14..vf17; a second volatile asm loads the pair (lwc1/mfc1 into \$t0/\$t1, qmtc2.ni), patches the rotation terms and multiplies the current matrix (vf1..vf4) by it in place. The pair loads are inside the asm (sc operand is \$sp). UNCONFIRMED: which slot is sin.
 */
void iosGetSinCosf(float *sc, float angle);

void iosRotCurrentMatrixY(float angle) {
    float sc[2];

    iosGetSinCosf(sc, angle);
    __asm__ __volatile__(
        "vmove.xyzw $vf17, $vf0\n"
        "vmr32.xyzw $vf16, $vf17\n"
        "vmr32.xyzw $vf15, $vf16\n"
        "vmr32.xyzw $vf14, $vf15\n");
    __asm__ __volatile__(
        "lwc1 $f1, 0x0(%0)\n"
        "lwc1 $f0, 0x4(%0)\n"
        "mfc1 $8, $f1\n"
        "mfc1 $9, $f0\n"
        "qmtc2.ni $8, $vf5\n"
        "qmtc2.ni $9, $vf6\n"
        "vaddx.x $vf14, $vf0, $vf5x\n"
        "vaddx.x $vf16, $vf0, $vf6x\n"
        "vsubx.z $vf14, $vf0, $vf6x\n"
        "vaddx.z $vf16, $vf0, $vf5x\n"
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
        "vmove.xyzw $vf4, $vf17\n" : : "r"(sc) : "$8", "$9", "$f0", "$f1", "memory");
}
