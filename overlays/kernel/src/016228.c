/* KERNEL.XFF @ 0x016228 (40 B) - iosWaitVU1
 * Evidence: volatile asm spin: five nops + `bc2t` back to the label (COP2 condition = VU1 running) + slot nop; returns 0 from C.
 */
int iosWaitVU1(void) {
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
        "bc2t 1b
"
        "nop
");
    return 0;
}
