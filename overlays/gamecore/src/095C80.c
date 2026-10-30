/* GAMECORE.XFF @ 0x095C80 (32 B) - GetSCRCharaAIWorkPtr
 * Evidence: ops ld lw sd; calls GetScriptCharacterClass; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
char *GetScriptCharacterClass(void);

char *GetSCRCharaAIWorkPtr(void) {
    return F(GetScriptCharacterClass(), char *, 0x1200);
}
