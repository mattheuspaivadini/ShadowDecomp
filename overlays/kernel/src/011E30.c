/* KERNEL.XFF @ 0x011E30 (32 B) - iosInitRandom
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosInitRandom(void *a0, void *a1, void *a2, float f12) {
    __asm__ __volatile__(
        "mfc1 $6, $f12\n"
        "qmtc2.ni $6, $vf5\n"
        "vaddw.x $vf6, $vf5, $vf0w\n"
        "vadd.x $vf5, $vf5, $vf5\n"
        "vrinit R, $vf5x\n"
        "vrxor R, $vf6x\n");
}
