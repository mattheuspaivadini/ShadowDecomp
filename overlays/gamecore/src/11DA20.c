/* GAMECORE.XFF @ 0x11DA20 (32 B) - SCRConditionPlayerTorch
 * Evidence: ops ld lw sd; calls getSCRDataCtrlWork, j getTorchInfo; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
char *getSCRDataCtrlWork(void);
int getTorchInfo(int t);

int SCRConditionPlayerTorch(void) {
    return getTorchInfo(F(getSCRDataCtrlWork(), int, 0x4078));
}
