/* GAMECORE.XFF @ 0x07B810 (40 B) - player_SetGripDamage
 * Evidence: the float argument is kept in `$f20` across `jal
 * GetSCRCharaAIWorkPtr` (frame slot 0x8, `mov.s` in the delay slot) and stored
 * into AI work +0x138.
 * UNCONFIRMED: the AI work field meaning and the callee prototype.
 
 */
void *GetSCRCharaAIWorkPtr(void);

void player_SetGripDamage(float damage) {
    *(float *)((char *)GetSCRCharaAIWorkPtr() + 0x138) = damage;
}
