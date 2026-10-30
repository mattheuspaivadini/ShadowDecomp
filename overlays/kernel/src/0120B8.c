/* KERNEL.XFF @ 0x0120B8 (180 B) - iosGetLengthPointToLine
 * Evidence: VU0-only body. `lqc2 $vf5,0(b)` / `lqc2 $vf6,0(a)` / `vsub.xyzw`
 * / `sqc2` to a 16-byte stack slot, then vsqrt of |a-b| via ACC/vsqrt/cfc2 $vi22
 * (the cfc2 value goes straight to the float compare through `mtc1 $f0`).
 * n1 = -(dot(a,v)) and n2 = dot(c,v) are each `qmfc2` of a vaddax/vmadday/vmaddz
 * chain (the `.x`-masked vaddw supplies the constant 1.0 in $vf7), then
 * n1 = (n1 + n2) / (l*l) with `div.s`, and the tail `qmtc2`/`vmulx.xyzw`/`sqc2`
 * scales v by n1 into *d. l is a float local (the `mtc1` after cfc2 proves a
 * float, not an int, temporary).
 * Flags: -fno-schedule-insns2 is required - with the default second scheduler the
 * `neg.s`/`mtc1 $f2` pair and the `lw`-after-`qmfc2` order come out swapped.
 * UNCONFIRMED: parameter names (d/a/b/c) and the v[4] scratch layout.
 */
void iosGetLengthPointToLine(float *d, float *a, float *b, float *c) {
    float v[4] __attribute__((aligned(16)));
    float l, n1, n2;

    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%1)\n"
        "lqc2 $vf6, 0x0(%2)\n"
        "vsub.xyzw $vf7, $vf5, $vf6\n"
        "sqc2 $vf7, 0x0(%0)\n" : : "r"(v), "r"(b), "r"(a) : "memory");
    __asm__ __volatile__(
        "lqc2 $vf7, 0x0(%1)\n"
        "vmul.xyz $vf7, $vf7, $vf7\n"
        "vmulax.w ACC, $vf0, $vf7x\n"
        "vmadday.w ACC, $vf0, $vf7y\n"
        "vmaddz.w $vf7, $vf0, $vf7z\n"
        "vsqrt Q, $vf7w\n"
        "vwaitq\n"
        "cfc2 %0, $vi22\n" : "=r"(l) : "r"(v) : "memory");
    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%1)\n"
        "lqc2 $vf6, 0x0(%2)\n"
        "vaddw.x $vf7, $vf0, $vf0w\n"
        "vmul.xyz $vf6, $vf5, $vf6\n"
        "vaddax.x ACC, $vf0, $vf6x\n"
        "vmadday.x ACC, $vf7, $vf6y\n"
        "vmaddz.x $vf6, $vf7, $vf6z\n"
        "qmfc2 %0, $vf6\n" : "=r"(n1) : "r"(a), "r"(v) : "memory");
    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%1)\n"
        "lqc2 $vf6, 0x0(%2)\n"
        "vaddw.x $vf7, $vf0, $vf0w\n"
        "vmul.xyz $vf6, $vf5, $vf6\n"
        "vaddax.x ACC, $vf0, $vf6x\n"
        "vmadday.x ACC, $vf7, $vf6y\n"
        "vmaddz.x $vf6, $vf7, $vf6z\n"
        "qmfc2 %0, $vf6\n" : "=r"(n2) : "r"(c), "r"(v) : "memory");
    n1 = -n1;
    n1 += n2;
    n1 = n1 / (l * l);
    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%1)\n"
        "qmtc2 %0, $vf6\n"
        "vmulx.xyzw $vf5, $vf5, $vf6x\n"
        "sqc2 $vf5, 0x0(%2)\n" : : "r"(n1), "r"(v), "r"(d) : "memory");
}
