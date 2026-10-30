/* GAMECORE.XFF @ 0x05CFB8 (40 B) - nico_setHorseBridleObjToHorseWork
 * Evidence: frame with `$s0`, `daddu $s0, $a1` in the `jal` delay slot, then
 * `sw $s0, 0x4248($v0)` on the AI work pointer: the second argument is stored.
 * UNCONFIRMED: the AI work field meaning and the first argument's role.
 
 */
void *GetSCRCharaAIWorkPtr(void);

void nico_setHorseBridleObjToHorseWork(int unused, int obj) {
    *(int *)((char *)GetSCRCharaAIWorkPtr() + 0x4248) = obj;
}
