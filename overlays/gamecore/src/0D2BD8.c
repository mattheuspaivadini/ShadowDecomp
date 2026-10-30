/* GAMECORE.XFF @ 0x0D2BD8 (56 B) - SCRConditionYamoriBDamageCheckFrontR
 * Evidence: `lwc1 [v0+0x41B0]`, `mtc1 $zero`, `c.le.s $f0(zero),$f1` + `bc1t`
 * to a `v1 = 1` path.
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);

int SCRConditionYamoriBDamageCheckFrontR(void) {
    return *(float *)(GetSCRCharaAIWorkPtr() + 0x41B0) >= 0.0f;
}
