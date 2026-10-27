/* KERNEL.XFF @ 0x00B220 (100 B) - iosCubicInterVectorXYZ
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosCubicInterVectorXYZ(void *a0, void *a1, void *a2, void *a3, float f12) {
    __asm__ __volatile__(
        "lui $1, 0x3F80\n"
        "mtc1 $1, $f0\n"
        "mul.s $f2, $f12, $f12\n"
        "lwc1 $f4, 0x0($7)\n"
        "sub.s $f0, $f0, $f12\n"
        "lwc1 $f5, 0x4($7)\n"
        "lwc1 $f3, 0x8($7)\n"
        "mul.s $f2, $f2, $f3\n"
        "add.s $f1, $f0, $f0\n"
        "mul.s $f0, $f0, $f0\n"
        "mul.s $f1, $f1, $f12\n"
        "mul.s $f0, $f0, $f4\n"
        "mul.s $f1, $f1, $f5\n"
        "add.s $f0, $f0, $f1\n"
        "add.s $f0, $f0, $f2\n"
        "mfc1 $8, $f0\n"
        "qmtc2.ni $8, $vf7\n"
        "lqc2 $vf5, 0x0($5)\n"
        "lqc2 $vf6, 0x0($6)\n"
        "vsubx.w $vf8, $vf0, $vf7x\n"
        "vmulax.xyz ACC, $vf5, $vf7x\n"
        "vmaddw.xyz $vf5, $vf6, $vf8w\n"
        "sqc2 $vf5, 0x0($4)\n");
}
