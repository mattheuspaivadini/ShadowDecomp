/* GAMECORE.XFF @ 0x07B2D0 (32 B) - nico_returnPlayerRidingFlag
 * Evidence: jal GetSCRCharaAIWorkPtr; load [v0+0xD98]
 * UNCONFIRMED: none
 */
char *GetSCRCharaAIWorkPtr(void);

int nico_returnPlayerRidingFlag(void) {
    return *(int *)(GetSCRCharaAIWorkPtr() + 0xD98);
}
