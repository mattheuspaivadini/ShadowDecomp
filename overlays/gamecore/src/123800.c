/* GAMECORE.XFF @ 0x123800 (32 B) - getAimIKWork
 * Evidence: ops ld lw sd; calls GetCharacterClass; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
char *GetCharacterClass(int obj);

int getAimIKWork(int obj) {
    return F(GetCharacterClass(obj), int, 0x1110);
}
