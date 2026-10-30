/* GAMECORE.XFF @ 0x05C350 (32 B) - SCRConditionHorseInterestExec
 * Evidence: a0 = v0+0x41B0, sibling j getInterestExec
 * UNCONFIRMED: none
 */
char *GetSCRCharaAIWorkPtr(void);
int getInterestExec(char *p);

int SCRConditionHorseInterestExec(void) {
    return getInterestExec(GetSCRCharaAIWorkPtr() + 0x41B0);
}
