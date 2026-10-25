/* KERNEL.XFF @ 0x00F478 (80 B) - DivQuaternion
 * Evidence: d = a * conj(b): a volatile VU0 asm conjugates b into a stack quad (vsubw.x/vmulx.xyz) and runs one volatile VU0 asm block holding the quaternion product (vmul/vaddy/vaddz/vsubx for w, vmulw + vopmula/vopmsub outer product for xyz), storing to d.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

void DivQuaternion(u_long128 *d, u_long128 *a, u_long128 *b) {
    u_long128 t;

    __asm__ __volatile__(
        "lqc2 $vf11, 0x0(%1)\n"
        "vsubw.x $vf5, $vf0, $vf0w\n"
        "vmulx.xyz $vf11, $vf11, $vf5x\n"
        "sqc2 $vf11, 0x0(%0)\n"
        "lqc2 $vf11, 0x0(%0)\n"
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
        "sqc2 $vf13, 0x0(%3)\n" : : "r"(&t), "r"(b), "r"(a), "r"(d) : "memory");
}
