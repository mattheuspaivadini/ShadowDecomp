/* GAMECORE.XFF @ 0x0CB228 (56 B) - SCRFuncKameMoveTimeSet
 * Evidence: `swc1 $f20`/`mov.s $f20,$f12`, `lwc1 [v0+0x41DC]`, `c.le.s $f1,$f0` +
 * `bc1tl` with `swc1 $f20 -> [v0+0x41DC]` in the delay slot.
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);

void SCRFuncKameMoveTimeSet(float value) {
    char *p = GetSCRCharaAIWorkPtr();
    if (*(float *)(p + 0x41DC) <= 0.0f) {
        *(float *)(p + 0x41DC) = value;
    }
}
