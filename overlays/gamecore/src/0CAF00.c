/* GAMECORE.XFF @ 0x0CAF00 (64 B) - SCRFuncKameCrackAnimMain
 * Evidence: same shape as SCRFuncKameFallPatienceCunterMain but with [v1+0x41CC].
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);
extern char gcGlobalVar;

void SCRFuncKameCrackAnimMain(void) {
    char *p = GetSCRCharaAIWorkPtr();
    if (*(float *)(p + 0x41CC) > 0.0f) {
        *(float *)(p + 0x41CC) -= *(float *)(&gcGlobalVar + 0x180);
    }
}
