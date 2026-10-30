/* GAMECORE.XFF @ 0x094858 (40 B) - SCRFuncPoseidonMissAttackInit
 * Evidence: frame with `$s0`, `daddu $s0, $a1` in the `jal` delay slot, then
 * `sw $s0, 0x41C4($v0)` on the AI work pointer: the second argument is stored.
 * UNCONFIRMED: the AI work field meaning and the first argument's role.
 
 */
void *GetSCRCharaAIWorkPtr(void);

void SCRFuncPoseidonMissAttackInit(int unused, int count) {
    *(int *)((char *)GetSCRCharaAIWorkPtr() + 0x41C4) = count;
}
