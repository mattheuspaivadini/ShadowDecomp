/* GAMECORE.XFF @ 0x0D2C48 (56 B) - SCRConditionYamoriBDamageCheckFrontL
 * Evidence: `lwc1 [v0+0x41B8]`, `mtc1 $zero`, `c.le.s $f0(zero),$f1` + `bc1t`
 * to a `v1 = 1` path.
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);

int SCRConditionYamoriBDamageCheckFrontL(void) {
    return *(float *)(GetSCRCharaAIWorkPtr() + 0x41B8) >= 0.0f;
}
