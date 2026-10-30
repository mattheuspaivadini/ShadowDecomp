/* GAMECORE.XFF @ 0x03ED00 (36 B) - SCRGetBossPartsDamageNum
 * Evidence: `jal GetSCRCharaAIWorkPtr`, `lw $v1, 0($v0)`, then `lw $v0,
 * 0x54($v1)` in the return slot: work->field_0 is a pointer and +0x54 is the
 * returned damage counter.
 * UNCONFIRMED: both field meanings and the callee prototype.
 
 */
void *GetSCRCharaAIWorkPtr(void);

int SCRGetBossPartsDamageNum(void) {
    return *(int *)(*(char **)GetSCRCharaAIWorkPtr() + 0x54);
}
