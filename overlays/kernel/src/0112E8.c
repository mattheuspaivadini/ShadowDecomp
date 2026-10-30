/* KERNEL.XFF @ 0x0112E8 (124 B) - GetQuaternionAxisRotInfo
 * Evidence: qmfc2.ni of the squared xyz length of dir (vmul.xyz + vaddy.x +
 * vaddz.x); `mtc1` of that value replaces the stack slot the C float compare
 * would need (the qmfc2/mtc1 pair must live inside the same volatile asm, so
 * gcc's `mtc1 $zero,$f0` for the 0.0f constant is emitted after it); zero length
 * stores ZUnitVector (lq/sq) and returns 0.0f in the same register (the `b` at
 * 0x11320 skips the acos call entirely); otherwise vrsqrt Q / vmulq.xyz
 * normalise dir into *out and the result is 2*iosGetACosfExact(dir[3])
 * (add.s f0,f0,f0). UNCONFIRMED: parameter names.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
extern u_long128 ZUnitVector;
float iosGetACosfExact(float x);

float GetQuaternionAxisRotInfo(u_long128 *out, float *dir) {
    register float fl __asm__("$f1");
    float r;

    __asm__ __volatile__(
        "lqc2 $vf7, 0x0(%1)\n"
        "vmul.xyz $vf7, $vf7, $vf7\n"
        "vaddy.x $vf7, $vf7, $vf7y\n"
        "vaddz.x $vf7, $vf7, $vf7z\n"
        "qmfc2.ni $2, $vf7\n"
        "mtc1 $2, $f1\n" : "=f"(fl) : "r"(dir) : "$2");
    if (fl == 0.0f) {
        *out = ZUnitVector;
        return 0.0f;
    }
    __asm__ __volatile__(
        "lqc2 $vf5, 0x0(%1)\n"
        "vmul.xyz $vf7, $vf5, $vf5\n"
        "vmulax.w ACC, $vf0, $vf7x\n"
        "vmadday.w ACC, $vf0, $vf7y\n"
        "vmaddz.w $vf7, $vf0, $vf7z\n"
        "vrsqrt Q, $vf0w, $vf7w\n"
        "vwaitq\n"
        "vmulq.xyz $vf5, $vf5, Q\n"
        "sqc2 $vf5, 0x0(%0)\n" : : "r"(out), "r"(dir) : "memory");
    r = iosGetACosfExact(dir[3]);
    return r + r;
}
