/* STATUS (Session 19, 2026-10-17): NON_MATCHING. best score 2 [cc=ee-gcc2.9-991111-01-dtls13010 -g0 -fno-delayed-branch -G0].
 * u64->float division (compiler-generated sign-split conversion); residual = GAS does not swap addiu sp into the jr slot because cc1 wraps the hazard nops + div.s in .set noreorder
 * The original .s stays in the build (asm/cod/011670.s); this C
 * draft (Session 19) is kept for the record. */
float TimerBusClock2Freq(unsigned long clk) {
    return 147456000.0f / clk;
}
