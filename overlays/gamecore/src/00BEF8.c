/* GAMECORE.XFF @ 0x00BEF8 (12 B) - ReleaseAI
 * Evidence: sw 0 -> gcGlobalVar+0x310
 * UNCONFIRMED: none
 */
extern int gcGlobalVar[];

void ReleaseAI(void) {
    gcGlobalVar[0x310 / 4] = 0;
}
