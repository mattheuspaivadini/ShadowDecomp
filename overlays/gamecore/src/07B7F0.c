/* GAMECORE.XFF @ 0x07B7F0 (32 B) - getPlayerWeaponHitAttr
 * Evidence: jal GetSCRCharaAIWorkPtr; load [v0+0x178]
 * UNCONFIRMED: none
 */
char *GetSCRCharaAIWorkPtr(void);

long getPlayerWeaponHitAttr(void) {
    return *(long *)(GetSCRCharaAIWorkPtr() + 0x178);
}
