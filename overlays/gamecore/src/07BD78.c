/* GAMECORE.XFF @ 0x07BD78 (32 B) - isWeaponTargetMarker
 * Evidence: jal GetSCRCharaAIWorkPtr; load [v0+0x50]
 * UNCONFIRMED: none
 */
char *GetSCRCharaAIWorkPtr(void);

int isWeaponTargetMarker(void) {
    return *(unsigned char *)(GetSCRCharaAIWorkPtr() + 0x50);
}
