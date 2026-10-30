/* GAMECORE.XFF @ 0x0CB280 (64 B) - SCRFuncKameMoveTimeMain
 * Evidence: `lwc1 [v1+0x41DC]`, `c.le.s $f0(zero),$f1` + `bc1f`, then
 * `[v1+0x41DC] -= gcGlobalVar+0x180`.
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);
extern char gcGlobalVar;

void SCRFuncKameMoveTimeMain(void) {
    char *p = GetSCRCharaAIWorkPtr();
    if (*(float *)(p + 0x41DC) >= 0.0f) {
        *(float *)(p + 0x41DC) -= *(float *)(&gcGlobalVar + 0x180);
    }
}
