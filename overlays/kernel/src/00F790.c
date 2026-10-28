/* KERNEL.XFF @ 0x00F790 (180 B) - RotQuaternionYExact
 * Evidence: the *Exact template of 010390 (iosGetSinCosf(-angle * 0.5f, &sc)
 * with sc[0] = cos at +0x10 and sc[1] = sin at +0x14, the 3-op VU0 scale into
 * the caller's quad at sp+0x00 and w <- cos at sp+0x0C), so the inlined helper
 * owns its `u_long128 sc` and the frame interleaves d/sc at 0x00/0x10; s0
 * keeps YUnitVector, s1 the d quad, s2 src and s3 out. The product block is the
 * same 12-op VU0 quaternion mul as quatMul but with the destination as a third
 * pointer (result stored through s3). UNCONFIRMED: helper/parameter names.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

extern float YUnitVector[];
void iosGetSinCosf(float angle, float *sc);

static __inline__ void scaleXYZW(void *d, void *s, float f) {
    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%1)\n"
        "qmtc2.ni %2, $vf6\n"
        "vmulx.xyzw $vf5, $vf5, $vf6x\n"
        "sqc2 $vf5, 0x0(%0)\n" : : "r"(d), "r"(s), "r"(f) : "memory");
}

static __inline__ void setExact(void *d, float deg, float *axis) {
    u_long128 sc;

    iosGetSinCosf(-deg * 0.5f, (float *)&sc);
    scaleXYZW(d, axis, ((float *)&sc)[1]);
    ((float *)d)[3] = ((float *)&sc)[0];
}

static __inline__ void quatMulTo(float *d, float *a, float *b) {
    __asm__ __volatile__(
        "lqc2 $vf11, 0x0(%1)\n"
        "lqc2 $vf12, 0x0(%2)\n"
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
        "sqc2 $vf13, 0x0(%0)\n" : : "r"(d), "r"(a), "r"(b) : "memory");
}

void RotQuaternionYExact(float *out, float *src, float angle) {
    u_long128 a;

    setExact(&a, angle, YUnitVector);
    quatMulTo(out, src, (float *)&a);
}
