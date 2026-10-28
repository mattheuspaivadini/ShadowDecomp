/* KERNEL.XFF @ 0x011568 (288 B) - iosGetSinf
 * Evidence: hand-written routine: every branch keeps a `nop` in its delay slot
 * (a compiled body in this module always fills them), so the whole function is
 * one volatile asm block. Structure: fold the argument into +/-x (a3 = 1 for a
 * negative input, 0 otherwise) with an out-of-range reduction by
 * `(float)(int)((angle +/- pi) / 2pi) * 2pi`; the coefficient quad at
 * .rodata+0x10E0 is read with lqc2 into vf15 and evaluated by the VU0
 * polynomial (qmtc2 of f3, vmr32 to copy x into .w, Horner chain in vf19),
 * negated with vsubx when a3 == 0; the result comes back through qmfc2/mtc1 to
 * f12, which the `jr $ra` delay slot copies to f0.
 * Notes for the lane: the asm needs `.set noreorder` (the EE gas otherwise
 * deletes the explicit delay-slot `nop`s and pads every branch with a second
 * one) and `$0` instead of `$zero` (this gas does not know the symbolic name);
 * the coefficient pointer is a `%hi/%lo` pair against D_kernel_rodata_10E0.
 * UNCONFIRMED: coefficient-table identity; the reduction is reconstructed from
 * the instruction shape only.
 */
extern unsigned char D_kernel_rodata_10E0[];

float iosGetSinf(float x) {
    register float r __asm__("$f12");

    r = x;
    __asm__ __volatile__(
        ".set noreorder\n"
        "lui $2, %%hi(D_kernel_rodata_10E0)\n"
        "addiu $2, $2, %%lo(D_kernel_rodata_10E0)\n"
        "mtc1 $0, $f0\n"
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
        "add.s $f3, $f0, $f12\n"
        "addiu $7, $0, 1\n"
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
        "sub.s $f3, $f0, $f12\n"
        "daddu $7, $0, $0\n"
        "4:\n"
        "mfc1 $8, $f3\n"
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
        "bnez $7, 5f\n"
        "nop\n"
        "vsubx.xyzw $vf18, $vf0, $vf18x\n"
        "5:\n"
        "qmfc2.ni $8, $vf18\n"
        "mtc1 $8, $f12\n"
        ".set reorder\n"
        : "+f"(r) : : "$2", "$7", "$8", "memory");
    return r;
}
