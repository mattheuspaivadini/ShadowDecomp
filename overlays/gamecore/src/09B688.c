/* GAMECORE.XFF @ 0x09B688 (32 B) - AI_JudgeNotCharaObjFunc
 * Evidence: ops ld sd; calls GetCharacterClass; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
char *GetCharacterClass(int obj);

int AI_JudgeNotCharaObjFunc(int obj) {
    return GetCharacterClass(obj) == 0;
}
