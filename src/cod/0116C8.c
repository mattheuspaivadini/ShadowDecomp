/* asm/cod/0116C8.s -> TimerFreq2BusClock.
 * timer TU: ee-gcc2.9-991111-01-dtls13010 -g0 -fno-delayed-branch -G0 (Session 19)
 * MATCHED. */
/* asm/cod/0116C8.s -> func_001116C8 @ 0x001116C8
 * f0 is materialised from the bit pattern 0x4D0CA000 (= 147456000.0f) with
 * `lui/ori` + `mtc1`, then `div.s f12, f0, f12` and func_00124D90(f12).
 * UNCONFIRMED: the constant's meaning; the bit pattern is evidence. */
float __fixunssfdi(float x);

float TimerFreq2BusClock(float x) {
    return __fixunssfdi(147456000.0f / x);
}
