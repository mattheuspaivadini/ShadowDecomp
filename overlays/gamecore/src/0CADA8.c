/* GAMECORE.XFF @ 0x0CADA8 (36 B) - SCRFuncKameDemoFlagSet
 * Evidence: `jal GetSCRCharaAIWorkPtr`, then `sw 1 -> [v0+0x41D8]`.
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);

void SCRFuncKameDemoFlagSet(void) {
    *(int *)(GetSCRCharaAIWorkPtr() + 0x41D8) = 1;
}
