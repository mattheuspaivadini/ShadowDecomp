/* GAMECORE.XFF @ 0x034DD0 (36 B) - SCRFuncBirdInitRotMode
 * Evidence: `jal GetSCRCharaAIWorkPtr`, then `sw 1` into the result +0x41D0.
 * UNCONFIRMED: the AI work field meaning (a rotation mode) and the callee
 * prototype (called with no arguments).
 
 */
void *GetSCRCharaAIWorkPtr(void);

void SCRFuncBirdInitRotMode(void) {
    *(int *)((char *)GetSCRCharaAIWorkPtr() + 0x41D0) = 1;
}
