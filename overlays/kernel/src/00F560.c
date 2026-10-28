/* KERNEL.XFF @ 0x00F560 (148 B) - MultiMatrixByQuaternion
 * Evidence: the same 24-op VU0 quaternion->matrix sequence as
 * GetZDirFromQuaternion (011038) with one operand: the pointer is materialised
 * as `daddu v0,sp,zero`, the 3x3 is stored at 0/0x10/0x20, `addiu v0,v0,0x30`
 * + `sqc2 vf0,0(v0)` writes the identity 4th column, then
 * `jal iosMulCurrentMatrixR` with `daddu a0,sp,zero`.
 * UNCONFIRMED: the callee prototype.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
void iosMulCurrentMatrixR(void *m);

void MultiMatrixByQuaternion(u_long128 *q) {
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
        "sqc2 $vf16, 0x20(%0)\n"
        "addiu $2, %0, 0x30\n"
        "sqc2 $vf0, 0x0($2)\n" : : "r"(p), "r"(q) : "memory");
    iosMulCurrentMatrixR(m);
}
