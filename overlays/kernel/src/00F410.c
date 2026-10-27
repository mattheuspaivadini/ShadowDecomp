/* KERNEL.XFF @ 0x00F410 (100 B) - SetQuaternionByAxisRotateVWithNoRegularize
 * Evidence: half = (short)angle >> 1; a volatile VU0 asm scales the axis by iosGetTableSin(half) into q (xyzw), then q[3] = iosGetTableCos(half).
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

void SetQuaternionByAxisRotateVWithNoRegularize(float *q, short angle, float *axis) {
    short half = angle >> 1;

    scaleXYZW(q, axis, iosGetTableSin(half));
    q[3] = iosGetTableCos(half);
}
