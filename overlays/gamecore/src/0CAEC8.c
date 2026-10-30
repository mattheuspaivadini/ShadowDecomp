/* GAMECORE.XFF @ 0x0CAEC8 (56 B) - SCRConditionKameCrackAnimChack
 * Evidence: `lwc1 [v0+0x41CC]`, `c.lt.s $f0(zero),$f1` + `bc1t` to a `v1 = 1` path.
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);

int SCRConditionKameCrackAnimChack(void) {
    return *(float *)(GetSCRCharaAIWorkPtr() + 0x41CC) > 0.0f;
}
