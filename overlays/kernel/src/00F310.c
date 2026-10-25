/* KERNEL.XFF @ 0x00F310 (116 B) - SetQuaternionByAxisRotateWithNoRegularize
 * Evidence: x/y/z ($f12..$f14) plus a 0 word form a stack vector held through a pointer; half = (short)angle >> 1 (sra 17); a volatile VU0 asm scales it by iosGetTableSin(half) into q, then q[3] = iosGetTableCos(half).
 */
static __inline__ void scaleXYZW(void *d, void *s, float f) {
    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%1)\n"
        "qmtc2.ni %2, $vf6\n"
        "vmulx.xyzw $vf5, $vf5, $vf6x\n"
        "sqc2 $vf5, 0x0(%0)\n" : : "r"(d), "r"(s), "r"(f) : "memory");
}
float iosGetTableSin(short angle);
float iosGetTableCos(short angle);

void SetQuaternionByAxisRotateWithNoRegularize(float *q, short angle, float x, float y, float z) {
    float v[4] __attribute__((aligned(16)));
    float *pv = v;
    short half = angle >> 1;

    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = 0.0f;
    scaleXYZW(q, pv, iosGetTableSin(half));
    q[3] = iosGetTableCos(half);
}
