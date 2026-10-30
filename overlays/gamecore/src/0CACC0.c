/* GAMECORE.XFF @ 0x0CACC0 (32 B) - SCRFuncKameFallPatienceCunterEnd
 * Evidence: jal GetSCRCharaAIWorkPtr, sw zero to field
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
char *GetSCRCharaAIWorkPtr(void);

void SCRFuncKameFallPatienceCunterEnd(void) {
    F(GetSCRCharaAIWorkPtr(), int, 0x41C0) = 0;
}
