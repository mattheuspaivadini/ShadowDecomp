/* KERNEL.XFF @ 0x011368 (116 B) - SetQuaternionByCosineAxisRotateV
 * Evidence: `lqc2 0(a1)` + vmul.xyz/vmulax/vmadday/vmaddz/vrsqrt/vwaitq/vmulq
 * normalise the axis into the 16-byte stack quad; then two scalar square roots
 * written with the old EE gas 2-operand encoding (`sqrt.s` source in the $f
 * field: 0x46010044 = sqrt.s $f1,$f1, 0x46000004 = sqrt.s $f0,$f0) give
 * w = sqrt((1+cos)/2) (stored with swc1 to +0xC *after* the sqc2) and
 * s = sqrt((1-cos)/2) (mfc1 -> qmtc2.ni -> vmulx.xyzw), so q = axis*sin and
 * q[3] = cos-half. US: cos == cos(angle).
 * The `daddu v0,sp,zero` operand copy needs the empty "+r" asm: a plain
 * `register ... asm("$2")` pin is folded back to $sp by 2.96.
 * UNCONFIRMED: helper names (normalizeAxis/scaleXYZW) and parameter names.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

static __inline__ float sq(float x) {
    float r;
    __asm__ __volatile__ ("sqrt.s %0,%1" : "=f"(r) : "f"(x));
    return r;
}

static __inline__ void normalizeAxis(void *d, void *s) {
    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%1)\n"
        "vmul.xyz $vf7, $vf5, $vf5\n"
        "vmulax.w ACC, $vf0, $vf7x\n"
        "vmadday.w ACC, $vf0, $vf7y\n"
        "vmaddz.w $vf7, $vf0, $vf7z\n"
        "vrsqrt Q, $vf0w, $vf7w\n"
        "vwaitq\n"
        "vmulq.xyz $vf5, $vf5, Q\n"
        "sqc2 $vf5, 0x0(%0)\n" : : "r"(d), "r"(s) : "memory");
}

static __inline__ void scaleXYZW(void *d, void *s, float f) {
    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%1)\n"
        "qmtc2.ni %2, $vf6\n"
        "vmulx.xyzw $vf5, $vf5, $vf6x\n"
        "sqc2 $vf5, 0x0(%0)\n" : : "r"(d), "r"(s), "r"(f) : "memory");
}

void SetQuaternionByCosineAxisRotateV(u_long128 *q, u_long128 *axis, float cos) {
    u_long128 n;
    float w;
    u_long128 *np;

    normalizeAxis(&n, axis);
    np = &n;
    __asm__ ("" : "+r"(np));
    w = sq((1.0f + cos) * 0.5f);
    scaleXYZW(q, np, sq((1.0f - cos) * 0.5f));
    ((float *)q)[3] = w;
}
