/* GAMECORE.XFF @ 0x05CA90 (36 B) - SRCConditionHorseHitColChack
 * Evidence: `jal GetSCRCharaAIWorkPtr`, then `ld $v0, 0x4238($v0)` (a 64-bit
 * load) and `sltu $v0, $zero, $v0` (result != 0) in the return slot.
 * UNCONFIRMED: the 8-byte AI work field meaning and the callee prototype.
 
 */
void *GetSCRCharaAIWorkPtr(void);

int SRCConditionHorseHitColChack(void) {
    return *(long *)((char *)GetSCRCharaAIWorkPtr() + 0x4238) != 0;
}
