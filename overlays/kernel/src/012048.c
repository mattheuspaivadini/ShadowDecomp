/* KERNEL.XFF @ 0x012048 (56 B) - iosGetStabXYVector
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
int iosGetStabXYVector(void *a0, void *a1) {
    __asm__ __volatile__(
        "lq $2, 0x0($5)\n"
        "sq $2, 0x0($4)\n"
        "sw $0, 0x8($4)\n"
        "lqc2 $vf5, 0x0($4)\n"
        "vmul.xyz $vf7, $vf5, $vf5\n"
        "vmulax.w ACC, $vf0, $vf7x\n"
        "vmadday.w ACC, $vf0, $vf7y\n"
        "vmaddz.w $vf7, $vf0, $vf7z\n"
        "vrsqrt Q, $vf0w, $vf7w\n"
        "vwaitq\n"
        "vmulq.xyz $vf5, $vf5, Q\n"
        "sqc2 $vf5, 0x0($4)\n");
}
