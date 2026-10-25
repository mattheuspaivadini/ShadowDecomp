/* KERNEL.XFF @ 0x011E50 (80 B) - iosGetRandom
 * Evidence: leaf with no frame, call or branch; the body is one volatile
 * asm block (the `jr $ra` delay slot stays a nop, which GCC does for a
 * volatile asm). UNCONFIRMED: parameter types/names (the asm reads the
 * argument registers directly).
 */
void iosGetRandom(void *a0, void *a1, void *a2, void *a3) {
    __asm__ __volatile__(
        "vrnext.x $vf5, R\n"
        "vrnext.x $vf5, R\n"
        "vrnext.x $vf5, R\n"
        "vrnext.x $vf5, R\n"
        "vrnext.x $vf5, R\n"
        "vrnext.x $vf5, R\n"
        "vrnext.x $vf5, R\n"
        "vrinit R, $vf5x\n"
        "vrnext.x $vf5, R\n"
        "vrnext.x $vf5, R\n"
        "vrnext.x $vf5, R\n"
        "vrnext.x $vf5, R\n"
        "vrnext.x $vf5, R\n"
        "vrnext.x $vf5, R\n"
        "vrnext.x $vf5, R\n"
        "vsubw.x $vf5, $vf5, $vf0w\n"
        "qmfc2.ni $7, $vf5\n"
        "mtc1 $7, $f0\n");
}
