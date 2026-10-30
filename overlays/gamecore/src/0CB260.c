/* GAMECORE.XFF @ 0x0CB260 (32 B) - SCRFuncKameMoveTimeReset
 * Evidence: jal GetSCRCharaAIWorkPtr, sw zero to field
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
char *GetSCRCharaAIWorkPtr(void);

void SCRFuncKameMoveTimeReset(void) {
    F(GetSCRCharaAIWorkPtr(), int, 0x41DC) = 0;
}
