/* KERNEL.XFF @ 0x00C9B0 (288 B) - iosSetCameraMatrix
 * Evidence: builds the inverse of a rigid transform. Two vopmula/vopmsub
 * cross products and two `vrsqrt Q` normalisations (vmul.xyz + vmulax.vmadday.
 * vmaddz chain) fill three rows of a 4x4 matrix that is first zeroed with
 * vmove+3x vmr32 through $vf14..$vf17 and four `sqc2` (the compiler's VU0
 * block clear). Rows land at a 0x40-byte local (`addiu v0,sp,0x40` is the
 * scratch quad for the first cross, `addiu v1,sp,0x20` / `addiu a2,sp,0x10`
 * are row 2 / row 1), the translation is copied in with `lq/sq` from $a1, and
 * the tail is the MMI transpose pextlw/pextuw/pcpyld/pcpyud + three
 * qmtc2.ni/vmulax/vmadday/vmaddz with the negated translation
 * ($vf9 = zero), stored as three `sq` + one `sqc2`. Everything after the
 * argument loads is one register block (numeric GPRs only - this gas rejects
 * $v0/$t0 spellings); the two stack quads are real locals (frame 0x50, leaf).
 * Verified byte-exact with -G0 and -G0 -fno-strict-aliasing.
 * UNCONFIRMED: parameter names/types; that the 3rd/4th arguments are the two
 * source axes (shipped order: $a3 first, then $a2).
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

void iosSetCameraMatrix(u_long128 *out, u_long128 *t, u_long128 *vx,
                        u_long128 *vy) {
    u_long128 m[4];
    u_long128 c;

    __asm__ __volatile__(
        "vmove.xyzw $vf17, $vf0\n"
        "vmr32.xyzw $vf16, $vf17\n"
        "vmr32.xyzw $vf15, $vf16\n"
        "vmr32.xyzw $vf14, $vf15\n"
        "sqc2 $vf14, %4\n"
        "sqc2 $vf15, 0x10($sp)\n"
        "sqc2 $vf16, 0x20($sp)\n"
        "sqc2 $vf17, 0x30($sp)\n"
        "addiu $2, $sp, 0x40\n"
        "lqc2 $vf5, 0x0(%3)\n"
        "lqc2 $vf6, 0x0(%2)\n"
        "vopmula.xyz ACC, $vf5, $vf6\n"
        "vopmsub.xyz $vf7, $vf6, $vf5\n"
        "vsub.w $vf7, $vf7, $vf7\n"
        "sqc2 $vf7, 0x0($2)\n"
        "lqc2 $vf5, 0x0($2)\n"
        "vmul.xyz $vf7, $vf5, $vf5\n"
        "vmulax.w ACC, $vf0, $vf7x\n"
        "vmadday.w ACC, $vf0, $vf7y\n"
        "vmaddz.w $vf7, $vf0, $vf7z\n"
        "vrsqrt Q, $vf0w, $vf7w\n"
        "vwaitq\n"
        "vmulq.xyz $vf5, $vf5, Q\n"
        "sqc2 $vf5, 0x0($sp)\n"
        "addiu $3, $sp, 0x20\n"
        "lqc2 $vf5, 0x0(%2)\n"
        "vmul.xyz $vf7, $vf5, $vf5\n"
        "vmulax.w ACC, $vf0, $vf7x\n"
        "vmadday.w ACC, $vf0, $vf7y\n"
        "vmaddz.w $vf7, $vf0, $vf7z\n"
        "vrsqrt Q, $vf0w, $vf7w\n"
        "vwaitq\n"
        "vmulq.xyz $vf5, $vf5, Q\n"
        "sqc2 $vf5, 0x0($3)\n"
        "addiu %2, $sp, 0x10\n"
        "lqc2 $vf5, 0x0($3)\n"
        "lqc2 $vf6, 0x0($sp)\n"
        "vopmula.xyz ACC, $vf5, $vf6\n"
        "vopmsub.xyz $vf7, $vf6, $vf5\n"
        "vsub.w $vf7, $vf7, $vf7\n"
        "sqc2 $vf7, 0x0(%2)\n"
        "lq $2, 0x0(%1)\n"
        "sq $2, 0x30($sp)\n"
        "lq $8, 0x0($sp)\n"
        "lq $9, 0x10($sp)\n"
        "lq $10, 0x20($sp)\n"
        "lqc2 $vf1, 0x30($sp)\n"
        "vmove.xyzw $vf2, $vf1\n"
        "vsub.xyz $vf1, $vf1, $vf1\n"
        "vmove.xyzw $vf9, $vf1\n"
        "qmfc2.ni $11, $vf1\n"
        "pextlw $12, $9, $8\n"
        "pextuw $13, $9, $8\n"
        "pextlw $14, $11, $10\n"
        "pextuw $15, $11, $10\n"
        "pcpyld $8, $14, $12\n"
        "pcpyud $9, $12, $14\n"
        "pcpyld $10, $15, $13\n"
        "qmtc2.ni $8, $vf3\n"
        "qmtc2.ni $9, $vf4\n"
        "qmtc2.ni $10, $vf8\n"
        "vmulax.xyz ACC, $vf3, $vf2x\n"
        "vmadday.xyz ACC, $vf4, $vf2y\n"
        "vmaddz.xyz $vf1, $vf8, $vf2z\n"
        "vsub.xyz $vf1, $vf9, $vf1\n"
        "sq $8, 0x0(%0)\n"
        "sq $9, 0x10(%0)\n"
        "sq $10, 0x20(%0)\n"
        "sqc2 $vf1, 0x30(%0)\n"
        : : "r"(out), "r"(t), "r"(vx), "r"(vy), "m"(m[0]), "m"(c)
        : "$2", "$3", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15",
          "memory");
}
