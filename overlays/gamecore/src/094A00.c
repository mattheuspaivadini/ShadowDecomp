/* GAMECORE.XFF @ 0x094A00 (56 B) - SCRConditionPoseidonDamageCoreTime
 * Evidence: `jal GetSCRCharaAIWorkPtr`, arg0 (float) saved in $f20, `lwc1
 * [v0+0x41D8]`, `c.le.s $f20,$f0` then `bc1t` to a `v0 = 1` path.
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);

int SCRConditionPoseidonDamageCoreTime(float time) {
    return time <= *(float *)(GetSCRCharaAIWorkPtr() + 0x41D8);
}
