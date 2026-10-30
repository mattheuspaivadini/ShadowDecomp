/* GAMECORE.XFF @ 0x0949B0 (32 B) - SCRFuncPoseidonAngryCountInit
 * Evidence: jal GetSCRCharaAIWorkPtr, sw zero to field
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
char *GetSCRCharaAIWorkPtr(void);

void SCRFuncPoseidonAngryCountInit(void) {
    F(GetSCRCharaAIWorkPtr(), int, 0x41D0) = 0;
}
