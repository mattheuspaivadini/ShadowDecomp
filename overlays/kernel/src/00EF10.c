/* KERNEL.XFF @ 0x00EF10 (84 B) - MultiCurrentQuaternion
 * Evidence: current = current * q: one volatile VU0 asm block holding the quaternion product (vmul/vaddy/vaddz/vsubx for w, vmulw + vopmula/vopmsub outer product for xyz); loads stack[top] into vf11 and q into vf12, stores to stack[top]. The quaternion stack is the 16-byte array at .bss+0xE2C0 indexed by .data+0x420 (see GetCurrentQuaternion).
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
extern int D_kernel_data_0420;
extern u_long128 D_kernel_bss_E2C0[];

void MultiCurrentQuaternion(u_long128 *q) {
    u_long128 *cur = &D_kernel_bss_E2C0[D_kernel_data_0420];

    __asm__ __volatile__(
        "lqc2 $vf11, 0x0(%0)\n"
        "lqc2 $vf12, 0x0(%1)\n"
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
        "sqc2 $vf13, 0x0(%0)\n" : : "r"(cur), "r"(q) : "memory");
}
