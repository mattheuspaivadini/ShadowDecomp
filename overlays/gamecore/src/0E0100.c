/* GAMECORE.XFF @ 0x0E0100 (48 B) - CAM_add_plane_offset_in_position
 * Evidence: build/s79/b/dis_all.txt (authority). Scale *a2 by s through a
 * stack quad, then add *a1: out = *a1 + *a2 * s. Same VU0 helper sequence as
 * 0DFCE0 / overlays/kernel/src/00B2F0.c.
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

void CAM_add_plane_offset_in_position(u_long128 *out, u_long128 *pos,
                                      u_long128 *plane, float s) {
    u_long128 tmp;

    scaleXYZ(&tmp, plane, s);
    addXYZ(out, pos, &tmp);
}
