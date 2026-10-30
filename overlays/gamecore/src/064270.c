/* GAMECORE.XFF @ 0x064270 (36 B) - SCRConditionLeoCheckArmorBroken
 * Evidence: `jal GetSCRCharaAIWorkPtr`, then `lw $v0, 0x41C0($v0)` and
 * `sltu $v0, $zero, $v0` (field != 0) in the return slot.
 * UNCONFIRMED: the AI work field meaning and the callee prototype.
 
 */
void *GetSCRCharaAIWorkPtr(void);

int SCRConditionLeoCheckArmorBroken(void) {
    return *(int *)((char *)GetSCRCharaAIWorkPtr() + 0x41C0) != 0;
}
