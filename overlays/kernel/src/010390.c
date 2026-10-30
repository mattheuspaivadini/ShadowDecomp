/* KERNEL.XFF @ 0x010390 (532 B) - GetQuaternionByEulerYXZExact
 * Evidence: same axis order as 010178 but the quaternion is built from
 * iosGetSinCosf(-angle * 0.5f, &sc) (sc[0]=cos at +0, sc[1]=sin at +4): the
 * 3-op VU0 scale (qmtc2/vmulx.xyzw) writes xyz and q[3] = cos in the same stack
 * quad. The per-block temporaries are the setter destination (an inlined helper
 * with its own u_long128 `sc`) so the frame interleaves quat/sc pairs at
 * 0x00/0x10, 0x20/0x30, 0x40/0x50.
 * UNCONFIRMED: helper/parameter names.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

extern float YUnitVector[];
extern float XUnitVector[];
extern float ZUnitVector[];
void iosGetSinCosf(float angle, float *sc);

static __inline__ void quatZero(void *q) {
    __asm__ __volatile__("sqc2 $vf0, 0x0(%0)\n" : : "r"(q) : "memory");
}

static __inline__ void scaleXYZW(void *d, void *s, float f) {
    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%1)\n"
        "qmtc2.ni %2, $vf6\n"
        "vmulx.xyzw $vf5, $vf5, $vf6x\n"
        "sqc2 $vf5, 0x0(%0)\n" : : "r"(d), "r"(s), "r"(f) : "memory");
}

static __inline__ void quatMul(float *d, float *s) {
    __asm__ __volatile__(
        "lqc2 $vf11, 0x0(%0)\n"
        "lqc2 $vf12, 0x0(%1)\n"
        "vmul.xyzw $vf13, $vf11, $vf12\n"
        "vaddy.x $vf13, $vf13, $vf13y\n"
        "vaddz.x $vf13, $vf13, $vf13z\n"
        "vsubx.w $vf13, $vf13, $vf13x\n"
        "vmulw.xyz $vf14, $vf12, $vf11w\n"
        "vmulw.xyz $vf15, $vf11, $vf12w\n"
        "vopmula.xyz ACC, $vf12, $vf11\n"
        "vopmsub.xyz $vf16, $vf11, $vf12\n"
        "vadd.xyz $vf13, $vf14, $vf15\n"
        "vadd.xyz $vf13, $vf13, $vf16\n"
        "sqc2 $vf13, 0x0(%0)\n" : : "r"(d), "r"(s) : "memory");
}

static __inline__ void quatNormalize(float *q) {
    __asm__ __volatile__(
        "lqc2 $vf14, 0x0(%0)\n"
        "vmul.xyzw $vf15, $vf14, $vf14\n"
        "vaddy.x $vf15, $vf15, $vf15y\n"
        "vaddz.x $vf15, $vf15, $vf15z\n"
        "vaddw.x $vf15, $vf15, $vf15w\n"
        "vrsqrt Q, $vf0w, $vf15x\n"
        "vwaitq\n"
        "vmulq.xyzw $vf15, $vf14, Q\n"
        "sqc2 $vf15, 0x0(%0)\n" : : "r"(q) : "memory");
}

static __inline__ void setExact(void *d, float deg, float *axis) {
    u_long128 sc;

    iosGetSinCosf(-deg * 0.5f, (float *)&sc);
    scaleXYZW(d, axis, ((float *)&sc)[1]);
    ((float *)d)[3] = ((float *)&sc)[0];
}

void GetQuaternionByEulerYXZExact(float *q, float x, float y, float z) {
    u_long128 a, b, c;
    int ret = 0;

    quatZero(q);
    if (y != 0.0f) {
        setExact(&a, y, YUnitVector);
        quatMul(q, (float *)&a);
        ret = 1;
    }
    if (x != 0.0f) {
        setExact(&b, x, XUnitVector);
        quatMul(q, (float *)&b);
        ret = 1;
    }
    if (z != 0.0f) {
        setExact(&c, z, ZUnitVector);
        quatMul(q, (float *)&c);
        ret = 1;
    }
    if (ret) {
        quatNormalize(q);
    }
}
