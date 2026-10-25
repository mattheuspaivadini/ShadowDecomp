/* KERNEL.XFF @ 0x00C310 (12 B) - iosGetCurrentMatrixTrans
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosGetCurrentMatrixTrans(void *a0) {
    __asm__ __volatile__(
        "sqc2 $vf4, 0x0($4)\n");
}
