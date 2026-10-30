/* GAMECORE.XFF @ 0x0CAC80 (64 B) - SCRFuncKameFallPatienceCunterMain
 * Evidence: `jal GetSCRCharaAIWorkPtr`, `lwc1 [v0+0x41C0]`, `c.lt.s $f0(zero),$f1` +
 * `bc1f`, then `[v1+0x41C0] -= gcGlobalVar+0x180`.
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);
extern char gcGlobalVar;

void SCRFuncKameFallPatienceCunterMain(void) {
    char *p = GetSCRCharaAIWorkPtr();
    if (*(float *)(p + 0x41C0) > 0.0f) {
        *(float *)(p + 0x41C0) -= *(float *)(&gcGlobalVar + 0x180);
    }
}
