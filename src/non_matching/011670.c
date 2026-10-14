/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 17 [cc=29, default].
 * float constant must come from .lit4; union bit pattern did not reproduce the load.
 * The original .s stays in the build (asm/cod/011670.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/011670.s -> func_00111670 @ 0x00111670 (0x54 bytes, 21 insns)
 *
 * Return 147456000.0f (0x4D0CA000, the EE bus clock in Hz) / f where f is
 * func_00124B90(a0); for a negative argument the input is first folded with
 * `(x >> 1) | (x & 1)` and the result doubled (`add.s $f1,$f0,$f0`).
 *
 *   if (a0 < 0)  f = func_00124B90((int)(((unsigned long long)a0 >> 1) | (a0 & 1))); f = f + f;
 *   else         f = func_00124B90((int)a0);
 *   return 0x4D0CA000 / f;
 *
 * Evidence details: `bltz` + `dsrl` (64-bit logical shift, no sign-extend pair
 * because the 32-bit value arrives sign-extended) and the `movz`-free
 * `andi`+`or`; the divisor is a single variable merged from both paths (hence
 * `mov.s $f1,$f0` in the first path's delay slot).
 * The constant MUST be materialised as `lui/ori $at` + `mtc1` (2 nops before
 * the div.s); a plain `147456000.0f` literal lands in .lit4 instead (see the
 * archived non-matching 0116C8.c), so it is written here as a bit pattern
 * through a union and left to scalar replacement.
 * MATCH GUESS: cc=29
 */
union C11670 {
    unsigned int bits;
    float value;
};

float func_00124B90(int a0);

float func_00111670(long long a0) {
    union C11670 c;
    float f;

    if (a0 < 0) {
        f = func_00124B90((int)(((unsigned long long)a0 >> 1) | (a0 & 1)));
        f = f + f;
    } else {
        f = func_00124B90((int)a0);
    }
    c.bits = 0x4D0CA000u;
    return c.value / f;
}
