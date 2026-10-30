/* GAMECORE.XFF @ 0x00BEE8 (16 B) - PauseAI
 * Evidence: sw 1 -> gcGlobalVar+0x310
 * UNCONFIRMED: none
 */
extern int gcGlobalVar[];

void PauseAI(void) {
    gcGlobalVar[0x310 / 4] = 1;
}
