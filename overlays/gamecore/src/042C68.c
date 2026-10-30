/* GAMECORE.XFF @ 0x042C68 (52 B) - SCRSetRootScaleRatio
 * Evidence: `$f12` kept in `$f20`, `jal GetCharacterClass`, a null test that
 * skips the `swc1 $f20,0x570` store and the `v0 = 1`, i.e. the null path
 * returns the pointer value (0) unchanged.
 * UNCONFIRMED: the class field meaning.
 
 */
struct CharacterClass {
    char pad[0x570];
    float rootScaleRatio;
};

struct CharacterClass *GetCharacterClass(void);

int SCRSetRootScaleRatio(float ratio) {
    struct CharacterClass *c = GetCharacterClass();

    if (c != 0) {
        c->rootScaleRatio = ratio;
        return 1;
    }
    return 0;
}
