/* KERNEL.XFF @ 0x011688 (280 B) - iosGetCosf
 * Evidence: hand-written routine (every branch keeps a `nop` in its delay slot,
 * which this module's compiled bodies never do), same reduction skeleton as
 * iosGetSinf: fold into a3 = (x < 0) and, out of range, subtract
 * `(float)(int)((angle +/- pi) / 2pi) * 2pi`; then the angle is placed at
 * pi/2 +/- x (add.s/sub.s with the pi/2 constant from 0x3FC90FDB) and the same
 * VU0 polynomial (coefficient quad at .rodata+0x10E0) is evaluated without the
 * sign fix-up; the result returns through qmfc2/mtc1 with the `jr $ra` delay
 * slot copying f12 to f0.
 * Notes for the lane: `.set noreorder` is required (otherwise this gas deletes
 * the explicit delay-slot `nop`s and pads every branch with a second one), and
 * `$0` must be spelled numerically; the `.rodata+0x10E0` coefficient quad is a
 * `%hi/%lo` pair against D_kernel_rodata_10E0.
 * UNCONFIRMED: coefficient-table identity; reduction reconstructed from shape.
 */
extern unsigned char D_kernel_rodata_10E0[];

float iosGetCosf(float x) {
    register float r __asm__("$f12");

    r = x;
    __asm__ __volatile__(
        ".set noreorder\n"
        "lui $2, %%hi(D_kernel_rodata_10E0)\n"
        "addiu $2, $2, %%lo(D_kernel_rodata_10E0)\n"
        "mtc1 $0, $f0\n"
        "lui $1, 0x3FC9\n"
        "ori $1, $1, 0xFDB\n"
        "mtc1 $1, $f3\n"
        "c.lt.s $f12, $f0\n"
        "bc1f 2f\n"
        "nop\n"
        "lui $1, 0xC049\n"
        "ori $1, $1, 0xFDB\n"
        "mtc1 $1, $f1\n"
        "c.le.s $f1, $f12\n"
        "bc1t 1f\n"
        "nop\n"
        "sub.s $f1, $f0, $f1\n"
        "lui $1, 0x40C9\n"
        "ori $1, $1, 0xFDB\n"
        "mtc1 $1, $f2\n"
        "sub.s $f4, $f1, $f12\n"
        "div.s $f4, $f4, $f2\n"
        "cvt.w.s $f4, $f4\n"
        "cvt.s.w $f4, $f4\n"
        "mul.s $f4, $f4, $f2\n"
        "add.s $f12, $f12, $f4\n"
        "c.lt.s $f12, $f0\n"
        "bc1f 3f\n"
        "nop\n"
        "1:\n"
        "add.s $f5, $f3, $f12\n"
        "j 4f\n"
        "nop\n"
        "2:\n"
        "lui $1, 0x4049\n"
        "ori $1, $1, 0xFDB\n"
        "mtc1 $1, $f1\n"
        "c.lt.s $f12, $f1\n"
        "bc1t 3f\n"
        "nop\n"
        "lui $1, 0x40C9\n"
        "ori $1, $1, 0xFDB\n"
        "mtc1 $1, $f2\n"
        "add.s $f4, $f1, $f12\n"
        "div.s $f4, $f4, $f2\n"
        "cvt.w.s $f4, $f4\n"
        "cvt.s.w $f4, $f4\n"
        "mul.s $f4, $f4, $f2\n"
        "sub.s $f12, $f12, $f4\n"
        "c.lt.s $f12, $f0\n"
        "bc1t 1b\n"
        "nop\n"
        "3:\n"
        "sub.s $f5, $f3, $f12\n"
        "4:\n"
        "mfc1 $8, $f5\n"
        "qmtc2.ni $8, $vf16\n"
        "lqc2 $vf15, 0x0($2)\n"
        "vmr32.w $vf16, $vf16\n"
        "vaddx.x $vf18, $vf0, $vf16x\n"
        "vmul.x $vf16, $vf16, $vf16\n"
        "vmulx.yzw $vf18, $vf18, $vf0x\n"
        "vmulw.xyzw $vf19, $vf15, $vf16w\n"
        "vmulx.xyzw $vf19, $vf19, $vf16x\n"
        "vmulx.xyz $vf19, $vf19, $vf16x\n"
        "vaddw.x $vf18, $vf18, $vf19w\n"
        "vmulx.xy $vf19, $vf19, $vf16x\n"
        "vaddz.x $vf18, $vf18, $vf19z\n"
        "vmulx.x $vf19, $vf19, $vf16x\n"
        "vaddy.x $vf18, $vf18, $vf19y\n"
        "vaddx.x $vf18, $vf18, $vf19x\n"
        "qmfc2.ni $7, $vf18\n"
        "mtc1 $7, $f12\n"
        ".set reorder\n"
        : "+f"(r) : : "$2", "$7", "$8", "memory");
    return r;
}
