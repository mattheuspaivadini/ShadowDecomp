/* GAMECORE.XFF @ 0x0CC8F8 (40 B) - SCRFuncUnagiSetPlayerGazePos
 * Evidence: `jal GetSCRCharaAIWorkPtr`, `jal GAMEUTIL_set_custom_boss_interest_position`
 * with `$a0 = $v0 + 0x5AF0`, then `$a0 = 0` and a tail `j
 * GAMEUTIL_set_auto_get_flag_boss_interest_position`.
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);

void GAMEUTIL_set_custom_boss_interest_position(void *pos);
void GAMEUTIL_set_auto_get_flag_boss_interest_position(int flag);

void SCRFuncUnagiSetPlayerGazePos(void) {
    char *p = GetSCRCharaAIWorkPtr();
    GAMEUTIL_set_custom_boss_interest_position(p + 0x5AF0);
    GAMEUTIL_set_auto_get_flag_boss_interest_position(0);
}
