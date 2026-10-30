/* GAMECORE.XFF @ 0x0CB2F8 (56 B) - SCRFuncKameNextAtkTimeInit
 * Evidence: same shape as SCRFuncKameMoveTimeSet but with [v0+0x41E0] and
 * `c.lt.s $f1,$f0`.
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);

void SCRFuncKameNextAtkTimeInit(float value) {
    char *p = GetSCRCharaAIWorkPtr();
    if (*(float *)(p + 0x41E0) < 0.0f) {
        *(float *)(p + 0x41E0) = value;
    }
}
