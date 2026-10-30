/* GAMECORE.XFF @ 0x0CB2C0 (56 B) - SCRConditionKameNextAtkTime
 * Evidence: `lwc1 [v0+0x41E0]`, `c.lt.s $f1,$f0(zero)` + `bc1t` to a `v1 = 1` path.
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);

int SCRConditionKameNextAtkTime(void) {
    return *(float *)(GetSCRCharaAIWorkPtr() + 0x41E0) < 0.0f;
}
