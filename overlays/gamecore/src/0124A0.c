/* GAMECORE.XFF @ 0x0124A0 (60 B) - nico_GetPlayerCharacterRidingHorseObject
 * Evidence: `beql` on the class pointer (returning 0 via `$v0 = 0`), then
 * `lw 0x950($v1)`, `xor` against the argument and `movz $v0,$zero,$v1`.
 * UNCONFIRMED: the class field at +0x950.
 
 */
void *GetCharacterClass(void *chara);

void *nico_GetPlayerCharacterRidingHorseObject(void *chara) {
    void *cls = GetCharacterClass(chara);
    void *horse;

    if (cls == 0)
        return 0;
    horse = *(void **)((char *)cls + 0x950);
    return horse == chara ? 0 : horse;
}
