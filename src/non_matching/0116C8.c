/* STATUS (Session 6, step 3): NON_MATCHING. The float constant 147456000.0f (bit pattern 0x4D0CA000) must be materialised with lui/ori + mtc1; ee-gcc puts it in .lit4 and loads it gp-relative (16 bytes short at cc=296, 8 at cc=29).
 * See docs/non-matching-backlog.md. */
/* asm/cod/0116C8.s -> func_001116C8 @ 0x001116C8
 * f0 is materialised from the bit pattern 0x4D0CA000 (= 147456000.0f) with
 * `lui/ori` + `mtc1`, then `div.s f12, f0, f12` and func_00124D90(f12).
 * UNCONFIRMED: the constant's meaning; the bit pattern is evidence. */
float func_00124D90(float x);

float func_001116C8(float x) {
    return func_00124D90(147456000.0f / x);
}
