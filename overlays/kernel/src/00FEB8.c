/* KERNEL.XFF @ 0x00FEB8 (68 B) - SetQuaternionByCosineAxisRotateVWithNoRegularize
 * Evidence: w = sqrt((c + 1) / 2), s = sqrt((1 - c) / 2) computed with volatile `sqrt.s` asm (no hazard nops, unlike GCC's builtin); a volatile VU0 asm scales the axis by s into q, then q[3] = w.
 */
static __inline__ float vsqrtf(float x) {
    float r;

    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

void SetQuaternionByCosineAxisRotateVWithNoRegularize(float *q, float c, float *axis) {
    float w = vsqrtf((c + 1.0f) * 0.5f);
    float s = vsqrtf((1.0f - c) * 0.5f);

    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%1)\n"
        "qmtc2.ni %2, $vf6\n"
        "vmulx.xyzw $vf5, $vf5, $vf6x\n"
        "sqc2 $vf5, 0x0(%0)\n" : : "r"(q), "r"(axis), "r"(s) : "memory");
    q[3] = w;
}
