/* GAMECORE.XFF @ 0x07BC20 (36 B) - player_GetBoundDamageLevel
 * Evidence: `jal GetSCRCharaAIWorkPtr`, `lw $v1, 0x184($v0)` (a pointer) then
 * `lwc1 $f0, 0x54($v1)`: a float read through one indirection.
 * UNCONFIRMED: both field meanings and the callee prototype.
 
 */
void *GetSCRCharaAIWorkPtr(void);

float player_GetBoundDamageLevel(void) {
    return *(float *)(*(char **)((char *)GetSCRCharaAIWorkPtr() + 0x184) + 0x54);
}
