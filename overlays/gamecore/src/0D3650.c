/* GAMECORE.XFF @ 0x0D3650 (40 B) - SCRFuncYamoriBSetBellyDamageParam
 * Evidence: `swc1 $f20`/`mov.s $f20,$f12`, `jal GetSCRCharaAIWorkPtr`, then
 * `swc1 $f20 -> [v0+0x41E8]`.
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);

void SCRFuncYamoriBSetBellyDamageParam(float value) {
    *(float *)(GetSCRCharaAIWorkPtr() + 0x41E8) = value;
}
