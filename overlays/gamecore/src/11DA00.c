/* GAMECORE.XFF @ 0x11DA00 (32 B) - SCRConditionMyselfKeepHit
 * Evidence: ops ld lw sd; calls GetCharacterClass; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
char *GetCharacterClass(int obj);

int SCRConditionMyselfKeepHit(int obj) {
    return F(GetCharacterClass(obj), int, 0xFF0);
}
