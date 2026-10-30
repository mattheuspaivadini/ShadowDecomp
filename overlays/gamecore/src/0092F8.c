/* GAMECORE.XFF @ 0x0092F8 (60 B) - GAMEUTIL_get_character_type
 * Evidence: null check on `$a0`, `jal GetCharacterClass`, null check on the
 * result, `lh 0x370($v0)` in the branch delay slot, and a single -1000000
 * (0xFFF0BDC0) block placed after the success return.
 * UNCONFIRMED: the class field at +0x370.
 
 */
void *GetCharacterClass(void *chara);

int GAMEUTIL_get_character_type(void *chara) {
    void *cls;

    if (chara != 0) {
        cls = GetCharacterClass(chara);
        if (cls != 0)
            return *(short *)((char *)cls + 0x370);
    }
    return -1000000;
}
