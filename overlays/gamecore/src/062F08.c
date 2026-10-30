/* GAMECORE.XFF @ 0x062F08 (36 B) - SCRFuncKirinFallRockTimerSetFlagOn
 * Evidence: `jal GetSCRCharaAIWorkPtr`, then `sw 1` into the result +0x41B8.
 * UNCONFIRMED: the AI work field meaning and the callee prototype.
 
 */
void *GetSCRCharaAIWorkPtr(void);

void SCRFuncKirinFallRockTimerSetFlagOn(void) {
    *(int *)((char *)GetSCRCharaAIWorkPtr() + 0x41B8) = 1;
}
