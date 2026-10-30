/* GAMECORE.XFF @ 0x009950 (60 B) - GAMEUTIL_get_riding_horse_object
 * Evidence: `beql` on the class pointer with `$v0 = 0` in the delay slot,
 * `lw 0x950($v0)`, `bne` against the argument with `$v0 = field` in the delay
 * slot, and a single shared `$v0 = 0` fall-through.
 * UNCONFIRMED: the class field at +0x950.
 
 */
void *GetCharacterClass(void *chara);

void *GAMEUTIL_get_riding_horse_object(void *chara) {
    void *cls = GetCharacterClass(chara);
    void *horse;

    if (cls != 0) {
        horse = *(void **)((char *)cls + 0x950);
        if (chara != horse)
            return horse;
    }
    return 0;
}
