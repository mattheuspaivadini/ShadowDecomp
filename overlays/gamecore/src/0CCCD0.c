/* GAMECORE.XFF @ 0x0CCCD0 (56 B) - SCRConditionUnageBossNotParentTime
 * Evidence: `swc1 $f20`/`mov.s $f20,$f12`, `lwc1 [v0+0x5B30]`, `c.lt.s $f20,$f0` +
 * `bc1t` to a `v0 = 1` path.
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);

int SCRConditionUnageBossNotParentTime(float time) {
    return time < *(float *)(GetSCRCharaAIWorkPtr() + 0x5B30);
}
