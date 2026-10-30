/* GAMECORE.XFF @ 0x094838 (32 B) - SCRConditionPoseidonGetRevolutionRayChack
 * Evidence: jal GetSCRCharaAIWorkPtr, lw field
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
char *GetSCRCharaAIWorkPtr(void);

int SCRConditionPoseidonGetRevolutionRayChack(void) {
    return F(GetSCRCharaAIWorkPtr(), int, 0x41B0);
}
