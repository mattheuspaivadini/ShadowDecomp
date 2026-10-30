/* GAMECORE.XFF @ 0x0D3378 (36 B) - SCRFuncYamoriBUnsetRandom
 * Evidence: `jal GetSCRCharaAIWorkPtr`, then `sw $zero -> [v0+0x41D4]` and
 * `sw $zero -> [v0+0x41D0]` (image order).
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);

void SCRFuncYamoriBUnsetRandom(void) {
    char *p = GetSCRCharaAIWorkPtr();
    *(int *)(p + 0x41D0) = 0;
    *(int *)(p + 0x41D4) = 0;
}
