/* KERNEL.XFF @ 0x00F018 (132 B) - RotCurrentQuaternionX
 * Evidence: the static at .text+0xF410 builds the rotation quaternion for (short)-angle about XUnitVector into a stack quad; a volatile VU0 asm multiplies stack[top] by it in place. The current quaternion is stack[top] (.bss+0xE2C0 indexed by .data+0x420). UNCONFIRMED: func_00F410 prototype.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
extern int D_kernel_data_0420;
extern u_long128 D_kernel_bss_E2C0[];
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
extern u_long128 XUnitVector;
void func_00F410(u_long128 *q, short angle, u_long128 *axis);

void RotCurrentQuaternionX(short angle) {
    u_long128 *cur = &D_kernel_bss_E2C0[D_kernel_data_0420];
    u_long128 r;

    func_00F410(&r, -angle, &XUnitVector);
    mulQuaternion(cur, cur, &r);
}
