/* GAMECORE.XFF @ 0x00B430 (24 B) - nico_defaultAI
 * Evidence: frame, `jal scrRun`, then `b .-3` back to the `jal`: an endless
 * `scrRun()` loop (the branch target is the call, so the loop body includes it).
 */
void scrRun(void);

void nico_defaultAI(void) {
    for (;;)
        scrRun();
}
