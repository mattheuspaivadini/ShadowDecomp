/* GAMECORE.XFF @ 0x0CB1F0 (56 B) - SCRConditionKameMoveTimeChack
 * Evidence: `lwc1 [v0+0x41DC]`, `c.le.s $f1,$f0(zero)` + `bc1t` to a `v1 = 1` path.
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);

int SCRConditionKameMoveTimeChack(void) {
    return *(float *)(GetSCRCharaAIWorkPtr() + 0x41DC) <= 0.0f;
}
