/* KERNEL.XFF @ 0x00F388 (72 B) - SetQuaternionByAxisRotateV
 * Evidence: a volatile VU0 asm normalises the axis (vmul.xyz, vmula/vmadd sum, vrsqrt, vmulq) into a 16-byte stack quad, then the stripped static at .text+0xF410 gets (q, angle, &axis); the angle is sign-extended from 16 bits (sll/sra 16). UNCONFIRMED: func_00F410 prototype.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
void func_00F410(u_long128 *q, short angle, u_long128 *axis);

void SetQuaternionByAxisRotateV(u_long128 *q, short angle, u_long128 *axis) {
    u_long128 n;

    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%1)\n"
        "vmul.xyz $vf7, $vf5, $vf5\n"
        "vmulax.w ACC, $vf0, $vf7x\n"
        "vmadday.w ACC, $vf0, $vf7y\n"
        "vmaddz.w $vf7, $vf0, $vf7z\n"
        "vrsqrt Q, $vf0w, $vf7w\n"
        "vwaitq\n"
        "vmulq.xyz $vf5, $vf5, Q\n"
        "sqc2 $vf5, 0x0(%0)\n" : : "r"(&n), "r"(axis) : "memory");
    func_00F410(q, angle, &n);
}
