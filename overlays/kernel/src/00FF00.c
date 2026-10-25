/* KERNEL.XFF @ 0x00FF00 (96 B) - SetQuaternionByAxisRotateVWithNoRegularizeRadian
 * Evidence: iosGetSinCosf(tmp, angle * 0.5f) into a 2-float stack buffer; a volatile VU0 asm scales the axis by tmp[1] (qmtc2.ni/vmulx.xyzw) into q, then q[3] = tmp[0]. UNCONFIRMED: which slot is sin.
 */
void iosGetSinCosf(float *sc, float angle);

void SetQuaternionByAxisRotateVWithNoRegularizeRadian(float *q, float *axis, float angle) {
    float sc[2];

    iosGetSinCosf(sc, angle * 0.5f);
    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%1)\n"
        "qmtc2.ni %2, $vf6\n"
        "vmulx.xyzw $vf5, $vf5, $vf6x\n"
        "sqc2 $vf5, 0x0(%0)\n" :  : "r"(q), "r"(axis), "r"(sc[1]) : "memory");
    q[3] = sc[0];
}
