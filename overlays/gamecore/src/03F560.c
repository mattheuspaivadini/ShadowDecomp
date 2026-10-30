/* GAMECORE.XFF @ 0x03F560 (24 B) - nico_boxtest
 * Evidence: jal scrRun; b back to jal
 * UNCONFIRMED: none
 */
void scrRun(void);

void nico_boxtest(void) {
    for (;;)
        scrRun();
}
