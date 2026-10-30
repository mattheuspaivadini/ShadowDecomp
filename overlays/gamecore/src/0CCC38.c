/* GAMECORE.XFF @ 0x0CCC38 (32 B) - SCRFuncUnageInitBossNotParentTime
 * Evidence: jal GetSCRCharaAIWorkPtr, sw zero to field
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
char *GetSCRCharaAIWorkPtr(void);

void SCRFuncUnageInitBossNotParentTime(void) {
    F(GetSCRCharaAIWorkPtr(), int, 0x5B30) = 0;
}
