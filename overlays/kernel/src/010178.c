/* KERNEL.XFF @ 0x010178 (536 B) - GetQuaternionByEulerYXZ
 * Evidence: `out = 0` quad (sqc2 vf0), then for y (f13), x (f12), z (f14) in that
 * order: if (angle != 0) SetQuaternionByAxisRotateVWithNoRegularize (stripped
 * .text+0xF410, $a1 = -(short)(angle*32768/PI), $a2 = Y/X/ZUnitVector), then a
 * VU0 quaternion product into *out; after the three blocks `if (flag)` runs the
 * vrsqrt normalise. The three 16-byte temporaries are distinct u_long128 locals
 * (slots 0/0x10/0x20) and the angle is converted through a short local before
 * the unary minus (sll 16 / negu / sra 16 order).
 * UNCONFIRMED: parameter names, the 32768/PI table-angle scale.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

extern float YUnitVector[];
extern float XUnitVector[];
extern float ZUnitVector[];
void SetQuaternionByAxisRotateVWithNoRegularize(float *q, short angle, float *axis);

static __inline__ void quatZero(void *q) {
    __asm__ __volatile__("sqc2 $vf0, 0x0(%0)\n" : : "r"(q) : "memory");
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

void GetQuaternionByEulerYXZ(float *q, float x, float y, float z) {
    u_long128 a, b, c;
    short s0, s1, s2;
    int ret = 0;

    quatZero(q);
    if (y != 0.0f) {
        s0 = (short)(y * 32768.0f / 3.1415926f);
        SetQuaternionByAxisRotateVWithNoRegularize((float *)&a, -s0, YUnitVector);
        quatMul(q, (float *)&a);
        ret = 1;
    }
    if (x != 0.0f) {
        s1 = (short)(x * 32768.0f / 3.1415926f);
        SetQuaternionByAxisRotateVWithNoRegularize((float *)&b, -s1, XUnitVector);
        quatMul(q, (float *)&b);
        ret = 1;
    }
    if (z != 0.0f) {
        s2 = (short)(z * 32768.0f / 3.1415926f);
        SetQuaternionByAxisRotateVWithNoRegularize((float *)&c, -s2, ZUnitVector);
        quatMul(q, (float *)&c);
        ret = 1;
    }
    if (ret) {
        quatNormalize(q);
    }
}
