/* GAMECORE.XFF @ 0x0DFCE0 (52 B) - CAM_get_camera_position_by_look_at
 * Evidence: build/s79/b/dis_all.txt (authority). scale (-s) of *a1 through a
 * stack quad, then add *a2: out = *a2 + *a1 * (-s).
 * VU0 macro-mode sequence matches overlays/kernel/src/00B2F0.c (volatile asm
 * helpers); the mfc1 before qmtc2.ni comes from the "r"(float) constraint.
 * UNCONFIRMED: parameter names (order is fixed by the register use).
 
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

static __inline__ void scaleXYZ(void *d, void *s, float f) {
    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%1)\n"
        "qmtc2.ni %2, $vf6\n"
        "vmulx.xyz $vf5, $vf5, $vf6x\n"
        "sqc2 $vf5, 0x0(%0)\n" : : "r"(d), "r"(s), "r"(f) : "memory");
}

static __inline__ void addXYZ(void *d, void *a, void *b) {
    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%1)\n"
        "lqc2 $vf6, 0x0(%2)\n"
        "vadd.xyz $vf5, $vf5, $vf6\n"
        "sqc2 $vf5, 0x0(%0)\n" : : "r"(d), "r"(a), "r"(b) : "memory");
}

void CAM_get_camera_position_by_look_at(u_long128 *out, u_long128 *a,
                                        u_long128 *b, float s) {
    u_long128 tmp;

    scaleXYZ(&tmp, a, -s);
    addXYZ(out, b, &tmp);
}
