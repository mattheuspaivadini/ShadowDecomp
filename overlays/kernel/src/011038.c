/* KERNEL.XFF @ 0x011038 (160 B) - GetZDirFromQuaternion
 * Evidence: the 24 VU0 ops build the rotation matrix of *(a1) in the classic
 * order (vaddw.xyz broadcasts 1.0, vopmula/vmadd/vmadw/vmsubw for the three
 * vmove.xyzw permutations); `daddu v0,sp,zero` + `sqc2 0/0x10/0x20(v0)` +
 * `addiu v0,v0,0x30` + `sqc2 vf0,0(v0)` mean one asm block whose pointer
 * operand lives in $v0 (GCC materialises a `register ... asm("$2")` pointer, and
 * the 4th column is written through `addiu $2,%0,0x30`), with the identity row
 * $vf0 as the 4th column. The direction is then the matrix column 3
 * (lwc1 0x20/0x24/0x28(sp)), stored as three floats + 0 at dir[3].
 * UNCONFIRMED: parameter names/units.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

void GetZDirFromQuaternion(float *dir, u_long128 *q) {
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
    dir[0] = ((float *)m)[8];
    dir[1] = ((float *)m)[9];
    dir[2] = ((float *)m)[10];
    dir[3] = 0.0f;
}
