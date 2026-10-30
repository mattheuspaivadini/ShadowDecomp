/* GAMECORE.XFF @ 0x03EC88 (32 B) - SCRGetBossWork
 * Evidence: lw 0(v0) after GetSCRCharaAIWorkPtr
 * UNCONFIRMED: none
 */
int *GetSCRCharaAIWorkPtr(void);

int SCRGetBossWork(void) {
    return *GetSCRCharaAIWorkPtr();
}
