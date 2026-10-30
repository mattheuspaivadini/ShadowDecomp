/* GAMECORE.XFF @ 0x0CB330 (64 B) - SCRFuncKameNextAtkTimeMain
 * Evidence: same shape as SCRFuncKameMoveTimeMain but with [v1+0x41E0].
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);
extern char gcGlobalVar;

void SCRFuncKameNextAtkTimeMain(void) {
    char *p = GetSCRCharaAIWorkPtr();
    if (*(float *)(p + 0x41E0) >= 0.0f) {
        *(float *)(p + 0x41E0) -= *(float *)(&gcGlobalVar + 0x180);
    }
}
