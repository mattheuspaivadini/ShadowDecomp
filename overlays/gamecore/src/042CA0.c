/* GAMECORE.XFF @ 0x042CA0 (52 B) - SCRSetCharaRootTurnScaleRatio
 * Evidence: `$f12` kept in `$f20`, `jal GetCharacterClass`, a null test that
 * skips the `swc1 $f20,0x574` store and the `v0 = 1`, i.e. the null path
 * returns the pointer value (0) unchanged.
 * UNCONFIRMED: the class field meaning.
 
 */
struct CharacterClass {
    char pad[0x574];
    float rootTurnScaleRatio;
};

struct CharacterClass *GetCharacterClass(void);

int SCRSetCharaRootTurnScaleRatio(float ratio) {
    struct CharacterClass *c = GetCharacterClass();

    if (c != 0) {
        c->rootTurnScaleRatio = ratio;
        return 1;
    }
    return 0;
}
