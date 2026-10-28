/* KERNEL.XFF @ 0x010F30 (260 B) - GetLimitationQuaternion
 * Evidence: `jal iosGetACosfExact` on src[3] then `add.s f1,f0,f0` = ang = 2*acos(w);
 * the two range tests are `c.lt.s f1,f0` (ang < 0) and, per arm, `c.lt.s f20,f0`
 * (limit < -ang) / `c.lt.s f20,f1` (limit < ang); the out-of-range path is
 * `sq v1,0x0(s0)` (128-bit copy of src into out, `lq v1,0x0(s1)` inlined into
 * each arm's delay slot) and returns 0 (v0 = 0 set at 0x010f58), i.e. the copy
 * block is the *last* block of the function - writing the two failures as
 * `goto copy` with the copy textually after `return 1` is what reproduces it
 * (an `if/else` with the copy inline makes gcc 2.96 cross-jump the two compares
 * into one shared `bc1t`).
 * `c.lt.s f1,f0` is re-evaluated at 0x010f98, so the half-angle select is a
 * second, independent `if (ang < 0.0f)` (0x3F00 = 0.5f, mul.s into f12).
 * Then the 9-op VU0 normalise (vmulax.w/vmadday.w/vmaddz.w + vrsqrt Q/vmulq.xyz)
 * into out, an `lwc1 0x4(sp)` + `mfc1`/`qmtc2.ni`/`vmulx.xyz` scale (sc[1]) and
 * `swc1` of sc[0] to out[3]; returns 1.
 * UNCONFIRMED: helper/callee prototypes and parameter names.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
float iosGetACosfExact(float x);
void iosGetSinCosf(void *out, float x);

static __inline__ void normalizeVec3(void *d, void *s) {
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

static __inline__ void scaleXYZ(void *d, float f) {
    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%0)\n"
        "qmtc2.ni %1, $vf6\n"
        "vmulx.xyz $vf5, $vf5, $vf6x\n"
        "sqc2 $vf5, 0x0(%0)\n" : : "r"(d), "r"(f) : "memory");
}

int GetLimitationQuaternion(u_long128 *out, float *src, float limit) {
    u_long128 sc;
    float ang;
    float half;

    ang = iosGetACosfExact(src[3]);
    ang = ang + ang;
    if (ang < 0.0f) {
        if (!(limit < -ang))
            goto copy;
    } else {
        if (!(limit < ang))
            goto copy;
    }
    if (ang < 0.0f) {
        half = -limit * 0.5f;
    } else {
        half = limit * 0.5f;
    }
    iosGetSinCosf(&sc, half);
    normalizeVec3(out, src);
    scaleXYZ(out, ((float *)&sc)[1]);
    ((float *)out)[3] = ((float *)&sc)[0];
    return 1;
copy:
    *(u_long128 *)out = *(u_long128 *)src;
    return 0;
}
