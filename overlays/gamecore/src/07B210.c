/* GAMECORE.XFF @ 0x07B210 (32 B) - getCurWeapon
 * Evidence: jal GetSCRCharaAIWorkPtr; load [v0+0x70]
 * UNCONFIRMED: none
 */
char *GetSCRCharaAIWorkPtr(void);

int getCurWeapon(void) {
    return *(int *)(GetSCRCharaAIWorkPtr() + 0x70);
}
