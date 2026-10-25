/* KERNEL.XFF @ 0x012170 (36 B) - iosGetInverseVectorXYZ
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
int iosGetInverseVectorXYZ(void *a0, void *a1) {
    __asm__ __volatile__(
        "lui $1, 0xBF80\n"
        "mtc1 $1, $f0\n"
        "mfc1 $2, $f0\n"
        "lqc2 $vf5, 0x0($5)\n"
        "qmtc2.ni $2, $vf6\n"
        "vmulx.xyz $vf5, $vf5, $vf6x\n"
        "sqc2 $vf5, 0x0($4)\n");
}
