/* KERNEL.XFF @ 0x011F58 (140 B) - iosGetArbitraryUpVectorElement
 * Evidence: picks the reference vector .data+0x4D0 when v[1] > 0.707, .data+0x480 when v[1] < -0.707, else .data+0x470; two volatile VU0 outer products (vopmula/vopmsub, w cleared) give tmp = v x ref and out = tmp x v. UNCONFIRMED: reference vector names.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
extern u_long128 D_kernel_data_04D0;
extern u_long128 D_kernel_data_0480;
extern u_long128 D_kernel_data_0470;

static __inline__ void outerXYZ(void *d, void *a, void *b) {
    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%1)\n"
        "lqc2 $vf6, 0x0(%2)\n"
        "vopmula.xyz ACC, $vf5, $vf6\n"
        "vopmsub.xyz $vf7, $vf6, $vf5\n"
        "vsub.w $vf7, $vf7, $vf7\n"
        "sqc2 $vf7, 0x0(%0)\n" : : "r"(d), "r"(a), "r"(b) : "memory");
}

void iosGetArbitraryUpVectorElement(float *out, float *v) {
    u_long128 tmp;
    u_long128 *up;

    if (0.706999957561492919921875f < v[1]) {
        up = &D_kernel_data_04D0;
    } else if (v[1] < -0.706999957561492919921875f) {
        up = &D_kernel_data_0480;
    } else {
        up = &D_kernel_data_0470;
    }
    outerXYZ(&tmp, v, up);
    outerXYZ(out, &tmp, v);
}
