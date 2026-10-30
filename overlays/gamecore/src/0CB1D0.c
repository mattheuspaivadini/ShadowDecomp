/* GAMECORE.XFF @ 0x0CB1D0 (32 B) - SCRConditionKameWallCaseFlagChack
 * Evidence: jal GetSCRCharaAIWorkPtr, lw field
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
char *GetSCRCharaAIWorkPtr(void);

int SCRConditionKameWallCaseFlagChack(void) {
    return F(GetSCRCharaAIWorkPtr(), int, 0x41D4);
}
