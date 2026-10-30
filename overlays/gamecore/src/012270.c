/* GAMECORE.XFF @ 0x012270 (32 B) - nico_ResetCharacterObjFallDownInfo
 * Evidence: jal GetCharacterClass; sibling j ResetCharacterClassFallDownInfo
 * UNCONFIRMED: none
 */
int GetCharacterClass(int c);
void ResetCharacterClassFallDownInfo(int cls);

void nico_ResetCharacterObjFallDownInfo(int c) {
    ResetCharacterClassFallDownInfo(GetCharacterClass(c));
}
