/* GAMECORE.XFF @ 0x06E6D0 (40 B) - SCRFuncNargaSetPlayerDamage
 * Evidence: frame with `$s0`, `daddu $s0, $a1` in the `jal` delay slot, then
 * `sw $s0, 0x5AA4($v0)` on the AI work pointer: the second argument is stored.
 * UNCONFIRMED: the AI work field meaning and the first argument's role.
 
 */
void *GetSCRCharaAIWorkPtr(void);

void SCRFuncNargaSetPlayerDamage(int unused, int damage) {
    *(int *)((char *)GetSCRCharaAIWorkPtr() + 0x5AA4) = damage;
}
