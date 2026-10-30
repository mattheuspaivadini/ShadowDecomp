/* GAMECORE.XFF @ 0x1070E0 (24 B) - setRunStopTurnAngleFastLegCtrlWork
 * Evidence: ops swc1
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void setRunStopTurnAngleFastLegCtrlWork(char *p, float v) {
    F(p, float, 0x4C) = v * 0.017453293f;
}
