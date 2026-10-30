/* GAMECORE.XFF @ 0x06BD98 (36 B) - SCRFuncMinoCSetPlayerInCorridorFlag
 * Evidence: `jal GetSCRCharaAIWorkPtr`, then `sw 1` into the result +0x41F4.
 * UNCONFIRMED: the AI work field meaning and the callee prototype.
 
 */
void *GetSCRCharaAIWorkPtr(void);

void SCRFuncMinoCSetPlayerInCorridorFlag(void) {
    *(int *)((char *)GetSCRCharaAIWorkPtr() + 0x41F4) = 1;
}
