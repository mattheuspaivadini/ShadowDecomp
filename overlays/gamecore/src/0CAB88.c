/* GAMECORE.XFF @ 0x0CAB88 (32 B) - SCRConditionTortoiseGeyserDamaged
 * Evidence: jal GetSCRCharaAIWorkPtr, lw field
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
char *GetSCRCharaAIWorkPtr(void);

int SCRConditionTortoiseGeyserDamaged(void) {
    return F(GetSCRCharaAIWorkPtr(), int, 0x41B0);
}
