/* GAMECORE.XFF @ 0x07B4D8 (32 B) - player_getWeaponType
 * Evidence: jal GetSCRCharaAIWorkPtr; load [v0+0x70]
 * UNCONFIRMED: none
 */
char *GetSCRCharaAIWorkPtr(void);

int player_getWeaponType(void) {
    return *(int *)(GetSCRCharaAIWorkPtr() + 0x70);
}
