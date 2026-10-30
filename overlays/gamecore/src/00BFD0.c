/* GAMECORE.XFF @ 0x00BFD0 (12 B) - GetCurrentGameAnimeTimeScaleRatio
 * Evidence: lwc1 gcGlobalVar+0x1A0
 * UNCONFIRMED: none
 */
extern float gcGlobalVar[];

float GetCurrentGameAnimeTimeScaleRatio(void) {
    return gcGlobalVar[0x1A0 / 4];
}
