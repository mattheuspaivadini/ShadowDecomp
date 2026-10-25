/* KERNEL.XFF @ 0x00B2F0 (140 B) - iosCubicBezierVectorXYZ
 * Evidence: three volatile VU0 asm scale steps (qmtc2.ni/vmulx.xyz) and two add steps (vadd.xyz) through a stack quad: d = p0*s^2 + p1*2st + p2*t^2 on xyz (inline helpers; the float factors are computed by the compiler between them).
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
static __inline__ void scaleXYZ(void *d, void *s, float f) {
    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%1)\n"
        "qmtc2.ni %2, $vf6\n"
        "vmulx.xyz $vf5, $vf5, $vf6x\n"
        "sqc2 $vf5, 0x0(%0)\n" : : "r"(d), "r"(s), "r"(f) : "memory");
}

static __inline__ void addXYZ(void *d, void *a, void *b) {
    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%1)\n"
        "lqc2 $vf6, 0x0(%2)\n"
        "vadd.xyz $vf5, $vf5, $vf6\n"
        "sqc2 $vf5, 0x0(%0)\n" : : "r"(d), "r"(a), "r"(b) : "memory");
}

void iosCubicBezierVectorXYZ(u_long128 *d, u_long128 *p, float t) {
    u_long128 tmp;
    float s = 1.0f - t;

    scaleXYZ(d, &p[0], s * s);
    scaleXYZ(&tmp, &p[1], (s + s) * t);
    addXYZ(d, d, &tmp);
    scaleXYZ(&tmp, &p[2], t * t);
    addXYZ(d, d, &tmp);
}
