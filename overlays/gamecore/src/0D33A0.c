/* GAMECORE.XFF @ 0x0D33A0 (32 B) - SCRFuncYamoriBSetAttackPosAndGazePosInit
 * Evidence: jal GetSCRCharaAIWorkPtr, sw zero to field
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
char *GetSCRCharaAIWorkPtr(void);

void SCRFuncYamoriBSetAttackPosAndGazePosInit(void) {
    F(GetSCRCharaAIWorkPtr(), int, 0x41C0) = 0;
}
