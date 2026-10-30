/* GAMECORE.XFF @ 0x0D2EC0 (40 B) - SCRFuncYamoriBSetCalcPosOffset
 * Evidence: `swc1 $f20`/`mov.s $f20,$f12`, `jal GetSCRCharaAIWorkPtr`, then
 * `swc1 $f20 -> [v0+0x41C4]`.
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);

void SCRFuncYamoriBSetCalcPosOffset(float value) {
    *(float *)(GetSCRCharaAIWorkPtr() + 0x41C4) = value;
}
