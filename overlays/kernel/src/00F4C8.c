/* KERNEL.XFF @ 0x00F4C8 (152 B) - GetInverseMatrixFromQuaternionPos
 * Evidence: the same 24-op VU0 quaternion->matrix sequence as
 * MultiMatrixByQuaternion (00F560) reading the quaternion from $a1 and keeping
 * the destination pointer in $v0 (`daddu v0,sp,zero`, stores at 0/0x10/0x20);
 * the 4th column comes from the position quad (`lqc2 vf4,0(a2)` + `vmove.w
 * vf4,vf0` = w <- 1, `sqc2 vf4,0x30(v0)`), and the inverse is taken with
 * iosInverseMatrix(out, m) (`daddu a1,sp,zero` = the temp matrix).
 * UNCONFIRMED: the callee prototype, parameter names.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
void iosInverseMatrix(void *d, void *m);

void GetInverseMatrixFromQuaternionPos(u_long128 *out, u_long128 *q, float *pos) {
    u_long128 m[4];
    register u_long128 *p __asm__("$2") = m;

    __asm__ __volatile__(
        "vaddw.xyz $vf12, $vf0, $vf0w\n"
        "lqc2 $vf11, 0x0(%1)\n"
        "vmr32.w $vf14, $vf0\n"
        "vmr32.w $vf15, $vf0\n"
        "vmr32.w $vf16, $vf0\n"
        "vopmula.xyz ACC, $vf11, $vf12\n"
        "vmadd.xyz $vf11, $vf0, $vf0\n"
        "vmadd.xyz $vf10, $vf11, $vf12\n"
        "vmul.xyz $vf13, $vf11, $vf10\n"
        "vopmula.xyz ACC, $vf11, $vf10\n"
        "vmaddw.xyz $vf15, $vf10, $vf11w\n"
        "vmsubw.xyz $vf16, $vf10, $vf11w\n"
        "vopmula.xyz ACC, $vf13, $vf12\n"
        "vmadd.xyz $vf17, $vf13, $vf12\n"
        "vopmula.xyz ACC, $vf15, $vf12\n"
        "vmadd.xyz $vf15, $vf0, $vf0\n"
        "vsub.xyz $vf14, $vf12, $vf17\n"
        "vmove.yz $vf17, $vf14\n"
        "vmove.y $vf14, $vf16\n"
        "vmove.y $vf16, $vf15\n"
        "vmove.y $vf15, $vf17\n"
        "vmove.z $vf14, $vf15\n"
        "vmove.z $vf15, $vf16\n"
        "vmove.z $vf16, $vf17\n"
        "sqc2 $vf14, 0x0(%0)\n"
        "sqc2 $vf15, 0x10(%0)\n"
        "sqc2 $vf16, 0x20(%0)\n" : : "r"(p), "r"(q) : "memory");
    __asm__ __volatile__(
        "lqc2 $vf4, 0x0(%1)\n"
        "vmove.w $vf4, $vf0\n"
        "sqc2 $vf4, 0x30(%0)\n" : : "r"(p), "r"(pos) : "memory");
    iosInverseMatrix(out, m);
}
