/* GAMECORE.XFF @ 0x0CCC08 (44 B) - SCRFuncUnageIncTblIdx
 * Evidence: `lw [v0+0x5ACC]`, `addiu 0x11`, `andi 0x1F`, `sw` back.
 * UNCONFIRMED: none
 
 */
char *GetSCRCharaAIWorkPtr(void);

void SCRFuncUnageIncTblIdx(void) {
    char *p = GetSCRCharaAIWorkPtr();
    *(int *)(p + 0x5ACC) = (*(int *)(p + 0x5ACC) + 0x11) & 0x1F;
}
