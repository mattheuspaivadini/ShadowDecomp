/* GAMECORE.XFF @ 0x094A88 (60 B) - SCRConditionPoseidonDamageCoreTimeMain
 * Evidence: `jal GetSCRCharaAIWorkPtr`, `lw [v1+0x41BC]` + `beqz`, then
 * `[v1+0x41D8] += gcGlobalVar+0x180` (HI16/LO16 pair).
 * UNCONFIRMED: gcGlobalVar field 0x180 meaning
 
 */
extern char gcGlobalVar;
char *GetSCRCharaAIWorkPtr(void);

void SCRConditionPoseidonDamageCoreTimeMain(void) {
    char *p = GetSCRCharaAIWorkPtr();
    if (*(int *)(p + 0x41BC) != 0) {
        *(float *)(p + 0x41D8) += *(float *)(&gcGlobalVar + 0x180);
    }
}
