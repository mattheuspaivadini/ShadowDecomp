/* GAMECORE.XFF @ 0x0CADD0 (32 B) - SCRFuncKameDemoFlagReset
 * Evidence: jal GetSCRCharaAIWorkPtr, sw zero to field
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
char *GetSCRCharaAIWorkPtr(void);

void SCRFuncKameDemoFlagReset(void) {
    F(GetSCRCharaAIWorkPtr(), int, 0x41D8) = 0;
}
