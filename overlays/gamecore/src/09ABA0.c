/* GAMECORE.XFF @ 0x09ABA0 (32 B) - AI_GetCurControlMode
 * Evidence: ops ld lw sd; calls GetCharacterClass; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
char *GetCharacterClass(int obj);

int AI_GetCurControlMode(int obj) {
    return F(GetCharacterClass(obj), int, 0x750);
}
