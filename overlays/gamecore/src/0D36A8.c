/* GAMECORE.XFF @ 0x0D36A8 (56 B) - SCRConditionYamoriBLessBellyDamageProgress
 * Evidence: `swc1 $f20`/`mov.s $f20,$f12`, `lwc1 [v0+0x41E4]`, `c.le.s $f0,$f20` +
 * `bc1t` to a `v0 = 1` path.
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);

int SCRConditionYamoriBLessBellyDamageProgress(float value) {
    return *(float *)(GetSCRCharaAIWorkPtr() + 0x41E4) <= value;
}
