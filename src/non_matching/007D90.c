/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 27 [cc=29, default].
 * double->int decompose via bit pattern.
 * The original .s stays in the build (asm/cod/007D90.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/007D90.s -> func_00107D90 @ 0x00107D90 (0x90 bytes, 36 insns)
 *
 * Double -> integer with rounding and clamping (the value is converted to a
 * 0..9999 range; called from asm/cod/007E20.s, which passes the raw 64-bit
 * pattern in $a0 and feeds the result to func_00108DB8). The EE o32 ABI keeps
 * a 64-bit value in ONE general register, which is why the argument arrives in
 * $a0 and is copied once to $a1:
 *
 *   dsll  $v0,$a1,1 ; dsrl32 $a2,$v0,21     ; (bits>>52)&0x7FF  (exp field)
 *   daddiu $a2,$a2,-0x433                   ; e = exp - 1075
 *   if (e <  -53) return 0;
 *   if (e >=  13) return 9999;
 *   sig = ((bits << 12) >> 12) | (1 << 52)  ; mantissa + implicit bit
 *   if (e >= 0) sig <<= e;
 *   else { n = -e; sig >>= n - 2;
 *          if ((sig & 3) == 3) sig = (sig >> 2) + 1; else sig >>= 2; }
 *   return (int)sig;                        ; dsll32/dsra32 sign-extend pair
 *
 * The 64-bit shifts (dsllv/dsrlv) and the trailing dsll32/dsra32 pair mean
 * the working variable is 64-bit and the returned expression is 32-bit (the
 * `dsll32 $r,0 / dsra32 $r,0` idiom = sign-extending an int into a 64-bit
 * result). The `daddu $a1,$a0` copy fits a bit-pattern reinterpretation of the
 * double (union) - a plain `long long` parameter would keep using $a0.
 * UNCONFIRMED: parameter is a `double` (alternative: `long long`).
 * MATCH GUESS: cc=296 (neighbour 007C48 is cc=296; the 2.96 duel of the
 * dsll/dsrl32 extraction) */
union U07D90 {
    double d;
    unsigned long long u;
};

long long func_00107D90(double x) {
    union U07D90 c;
    int e;
    int n;

    c.d = x;
    e = (int)((c.u >> 52) & 0x7FF) - 0x433;
    if (e < -53)
        return 0;
    if (e >= 13)
        return 9999;
    c.u = (c.u & 0xFFFFFFFFFFFFFLL) | 0x10000000000000LL;
    if (e >= 0) {
        c.u <<= e;
    } else {
        n = -e;
        c.u >>= n - 2;
        if ((c.u & 3) == 3)
            c.u = (c.u >> 2) + 1;
        else
            c.u >>= 2;
    }
    return (int)c.u;
}
