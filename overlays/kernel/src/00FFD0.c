/* KERNEL.XFF @ 0x00FFD0 (216 B) - GetStabYRotQuaternion
 * Evidence: the first VU0 asm builds the perpendicular component of *src into
 * the stack quad t[1] (vmr32 rotl, vmul, vaddy/vsubw/vsubx/vsubz/vaddz to zero
 * w, then w = -0 * 1.0); func_00DB38(&t[0], YUnitVector, &t[1], ZUnitVector)
 * builds the y-rotation quaternion into t[0]; mulQuaternion(q, &t[0], src);
 * normalizeQuaternion(q). The image keeps q in $s0 and src in $s1 even though
 * src is referenced first, so q is pinned to $16 and forced live with an empty
 * "+r" asm (a plain `register ... asm("$16")` declaration is folded away).
 * UNCONFIRMED: helper names, func_00DB38 prototype, global names.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
extern u_long128 YUnitVector;
extern u_long128 ZUnitVector;
void func_00DB38(u_long128 *q, u_long128 *y, u_long128 *v, u_long128 *z);

static __inline__ void mulQuaternion(void *d, void *a, void *b) {
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

static __inline__ void normalizeQuaternion(void *q) {
    __asm__ __volatile__(
        "lqc2 $vf14, 0x0(%0)\n"
        "vmul.xyzw $vf15, $vf14, $vf14\n"
        "vaddy.x $vf15, $vf15, $vf15y\n"
        "vaddz.x $vf15, $vf15, $vf15z\n"
        "vaddw.x $vf15, $vf15, $vf15w\n"
        "vrsqrt Q, $vf0w, $vf15x\n"
        "vwaitq\n"
        "vmulq.xyzw $vf15, $vf14, Q\n"
        "sqc2 $vf15, 0x0(%0)\n" : : "r"(q) : "memory");
}

void GetStabYRotQuaternion(u_long128 *q, u_long128 *src) {
    u_long128 t[2];
    register u_long128 *d __asm__("$16");

    d = q;
    __asm__ ("" : "+r"(d));
    __asm__ __volatile__(
        "lqc2 $vf4, 0x0(%1)\n"
        "vmul.xyzw $vf5, $vf4, $vf4\n"
        "vmr32.xyzw $vf6, $vf4\n"
        "vmul.xyzw $vf7, $vf6, $vf4\n"
        "vaddy.z $vf6, $vf0, $vf7y\n"
        "vsubw.z $vf6, $vf6, $vf7w\n"
        "vsubx.y $vf6, $vf0, $vf5x\n"
        "vsubz.y $vf6, $vf6, $vf5z\n"
        "vaddz.x $vf6, $vf7, $vf7z\n"
        "vsub.w $vf6, $vf0, $vf0\n"
        "vadd.w $vf5, $vf0, $vf0\n"
        "vmulw.xyz $vf6, $vf6, $vf5w\n"
        "vaddw.y $vf6, $vf6, $vf0w\n"
        "sqc2 $vf6, 0x0(%0)\n" : : "r"(&t[1]), "r"(src) : "memory");
    func_00DB38(&t[0], &YUnitVector, &t[1], &ZUnitVector);
    mulQuaternion(d, &t[0], src);
    normalizeQuaternion(d);
}
