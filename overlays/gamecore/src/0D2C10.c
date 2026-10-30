/* GAMECORE.XFF @ 0x0D2C10 (56 B) - SCRConditionYamoriBDamageCheckBackR
 * Evidence: `lwc1 [v0+0x41B4]`, `mtc1 $zero`, `c.le.s $f0(zero),$f1` + `bc1t`
 * to a `v1 = 1` path.
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);

int SCRConditionYamoriBDamageCheckBackR(void) {
    return *(float *)(GetSCRCharaAIWorkPtr() + 0x41B4) >= 0.0f;
}
