/* GAMECORE.XFF @ 0x00BED8 (12 B) - GetGameTimeScaleRatio
 * Evidence: lwc1 gcGlobalVar+0x19C
 * UNCONFIRMED: none
 */
extern float gcGlobalVar[];

float GetGameTimeScaleRatio(void) {
    return gcGlobalVar[0x19C / 4];
}
