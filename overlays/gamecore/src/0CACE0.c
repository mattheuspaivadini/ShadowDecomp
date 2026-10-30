/* GAMECORE.XFF @ 0x0CACE0 (56 B) - SCRConditionKameFallPatienceCunterCheck
 * Evidence: `lwc1 [v0+0x41C0]`, `mtc1 $zero`, `c.lt.s $f0,$f1` + `bc1t` to a `v1 = 1`
 * path, else `v1 = 0`.
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);

int SCRConditionKameFallPatienceCunterCheck(void) {
    return *(float *)(GetSCRCharaAIWorkPtr() + 0x41C0) > 0.0f;
}
