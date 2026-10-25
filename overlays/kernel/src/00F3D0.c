/* KERNEL.XFF @ 0x00F3D0 (64 B) - SetQuaternionByAxisRotateVExact
 * Evidence: a volatile VU0 asm normalises the axis (vmul, vmula*, vrsqrt, vmulq)
 * into a stack quad, then calls the stripped static at .text+0xFF00 with
 * ($a0 forwarded, &normalised, $f12 forwarded). UNCONFIRMED: func_00FF00's
 * prototype (the angle is inferred from the untouched $f12).
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
void func_00FF00(u_long128 *q, u_long128 *axis, float angle);

void SetQuaternionByAxisRotateVExact(u_long128 *q, u_long128 *axis, float angle) {
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
    func_00FF00(q, &n, angle);
}
