/* asm/cod/011670.s -> TimerBusClock2Freq.
 * u64->float div; TU built with -G0 (immediate fp const)
 * MATCHED. */
float TimerBusClock2Freq(unsigned long clk) {
    return 147456000.0f / clk;
}
