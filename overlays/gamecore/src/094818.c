/* GAMECORE.XFF @ 0x094818 (32 B) - SCRFuncPoseidonResetRevolutionDirection
 * Evidence: jal GetSCRCharaAIWorkPtr, sw zero to field
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
char *GetSCRCharaAIWorkPtr(void);

void SCRFuncPoseidonResetRevolutionDirection(void) {
    F(GetSCRCharaAIWorkPtr(), int, 0x41C8) = 0;
}
