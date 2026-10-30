/* GAMECORE.XFF @ 0x05C498 (40 B) - SCRFuncHorseAdvertisFlag
 * Evidence: frame with `$s0`, `daddu $s0, $a1` in the `jal` delay slot, then
 * `sw $s0, 0x4204($v0)` on the AI work pointer: the second argument is stored.
 * UNCONFIRMED: the AI work field meaning and the first argument's role.
 
 */
void *GetSCRCharaAIWorkPtr(void);

void SCRFuncHorseAdvertisFlag(int unused, int flag) {
    *(int *)((char *)GetSCRCharaAIWorkPtr() + 0x4204) = flag;
}
