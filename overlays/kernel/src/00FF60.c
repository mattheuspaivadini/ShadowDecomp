/* KERNEL.XFF @ 0x00FF60 (108 B) - GetYRotQuaternionFromDir
 * Evidence: YUnitVector when dir[0] < 0, else YUnitVectorInv; c = dir[2]; w/s by volatile `sqrt.s` asm as in SetQuaternionByCosineAxisRotateVWithNoRegularize; the axis is scaled by s into q and q[3] = w.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
static __inline__ float vsqrtf(float x) {
    float r;

    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}
static __inline__ void scaleXYZW(void *d, void *s, float f) {
    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%1)\n"
        "qmtc2.ni %2, $vf6\n"
        "vmulx.xyzw $vf5, $vf5, $vf6x\n"
        "sqc2 $vf5, 0x0(%0)\n" : : "r"(d), "r"(s), "r"(f) : "memory");
}
extern u_long128 YUnitVector;
extern u_long128 YUnitVectorInv;

void GetYRotQuaternionFromDir(float *q, float *dir) {
    u_long128 *axis;
    float c;
    float w;
    float s;

    if (dir[0] < 0.0f) {
        axis = &YUnitVector;
    } else {
        axis = &YUnitVectorInv;
    }
    c = dir[2];
    w = vsqrtf((c + 1.0f) * 0.5f);
    s = vsqrtf((1.0f - c) * 0.5f);
    scaleXYZW(q, axis, s);
    q[3] = w;
}
