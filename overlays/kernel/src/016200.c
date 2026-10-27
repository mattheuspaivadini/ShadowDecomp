/* KERNEL.XFF @ 0x016200 (40 B) - iosWaitDMA
 * Evidence: volatile asm spin: five nops + `bc0f` back to the label (CP0 condition = DMA busy) + slot nop; returns 0 from C.
 */
int iosWaitDMA(void) {
    __asm__ __volatile__(
        "1:
"
        "nop
"
        "nop
"
        "nop
"
        "nop
"
        "nop
"
        "bc0f 1b
"
        "nop
");
    return 0;
}
