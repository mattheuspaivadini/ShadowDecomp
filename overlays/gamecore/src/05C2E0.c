/* GAMECORE.XFF @ 0x05C2E0 (44 B) - SCRFuncHorseInterestInit
 * Evidence: `$a0` is saved in `$s0` across `jal GetSCRCharaAIWorkPtr`, then
 * `$a0 = $s0`, `$a1 = $v0 + 0x41B0` and a sibling `j` to `initInterestWork`.
 * UNCONFIRMED: the AI work field meaning and the callee prototype.
 
 */
void *GetSCRCharaAIWorkPtr(void);
void initInterestWork(void *arg, void *work);

void SCRFuncHorseInterestInit(void *arg) {
    initInterestWork(arg, (char *)GetSCRCharaAIWorkPtr() + 0x41B0);
}
