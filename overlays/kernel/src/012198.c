/* KERNEL.XFF @ 0x012198 (84 B) - iosGetExceptAxisVector
 * Evidence: dot(a,b) is computed in vf6 and read with qmfc2 into a float local
 * (GCC emits mtc1 because the second asm takes that local with an "f"
 * constraint); that asm does its own mfc1 (the shipped `mfc1 $2,$f0` sits
 * before the lqc2), broadcasts the scalar with qmtc2/vmulx.xyz and spills
 * b*scalar through a 16-byte aligned stack quad; the third asm subtracts the
 * quad from a and sqc2's to *d. UNCONFIRMED: parameter names.
 */
void iosGetExceptAxisVector(float *d, float *a, float *b) {
    float t[4] __attribute__((aligned(16)));
    float f;

    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%1)\n"
        "lqc2 $vf6, 0x0(%2)\n"
        "vaddw.x $vf7, $vf0, $vf0w\n"
        "vmul.xyz $vf6, $vf5, $vf6\n"
        "vaddax.x ACC, $vf0, $vf6x\n"
        "vmadday.x ACC, $vf7, $vf6y\n"
        "vmaddz.x $vf6, $vf7, $vf6z\n"
        "qmfc2 %0, $vf6\n" : "=r"(f) : "r"(a), "r"(b) : "memory");
    __asm__ __volatile__(
        "mfc1 $2, %0\n"
        "lqc2 $vf5, 0x0(%1)\n"
        "qmtc2 $2, $vf6\n"
        "vmulx.xyz $vf5, $vf5, $vf6x\n"
        "sqc2 $vf5, 0x0(%2)\n" : : "f"(f), "r"(b), "r"(t) : "$2", "memory");
    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%1)\n"
        "lqc2 $vf6, 0x0(%2)\n"
        "vsub.xyz $vf5, $vf5, $vf6\n"
        "sqc2 $vf5, 0x0(%0)\n" : : "r"(d), "r"(a), "r"(t) : "memory");
}
