/* GAMECORE.XFF @ 0x09B090 (60 B) - AI_GetSideSignalFromDirLev
 * Evidence: build/s79/b/dis_all.txt (authority). One VU0 outer product of the
 * two direction vectors (w cleared), the sign test reads lane 1 of the stored
 * quad; 0.0f <= y returns -1, otherwise 1.
 * UNCONFIRMED: parameter names.
 
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

static __inline__ void outerXYZ(void *d, void *a, void *b) {
    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%1)\n"
        "lqc2 $vf6, 0x0(%2)\n"
        "vopmula.xyz ACC, $vf5, $vf6\n"
        "vopmsub.xyz $vf7, $vf6, $vf5\n"
        "vsub.w $vf7, $vf7, $vf7\n"
        "sqc2 $vf7, 0x0(%0)\n" : : "r"(d), "r"(a), "r"(b) : "memory");
}

int AI_GetSideSignalFromDirLev(float *a, float *b) {
    u_long128 tmp;

    outerXYZ(&tmp, a, b);
    return 0.0f <= ((float *)&tmp)[1] ? -1 : 1;
}
