/* GAMECORE.XFF @ 0x00B448 (24 B) - nico_volatileDefaultAI
 * Evidence: jal scrRun; b back to jal
 * UNCONFIRMED: none
 */
void scrRun(void);

void nico_volatileDefaultAI(void) {
    for (;;)
        scrRun();
}
