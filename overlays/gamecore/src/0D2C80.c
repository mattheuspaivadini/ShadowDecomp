/* GAMECORE.XFF @ 0x0D2C80 (56 B) - SCRConditionYamoriBDamageCheckBackL
 * Evidence: `lwc1 [v0+0x41BC]`, `mtc1 $zero`, `c.le.s $f0(zero),$f1` + `bc1t`
 * to a `v1 = 1` path.
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);

int SCRConditionYamoriBDamageCheckBackL(void) {
    return *(float *)(GetSCRCharaAIWorkPtr() + 0x41BC) >= 0.0f;
}
