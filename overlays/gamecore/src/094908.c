/* GAMECORE.XFF @ 0x094908 (32 B) - SCRFuncPoseidonResetPlayerTerrLog
 * Evidence: jal GetSCRCharaAIWorkPtr, sw zero to field
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
char *GetSCRCharaAIWorkPtr(void);

void SCRFuncPoseidonResetPlayerTerrLog(void) {
    F(GetSCRCharaAIWorkPtr(), int, 0x41CC) = 0;
}
