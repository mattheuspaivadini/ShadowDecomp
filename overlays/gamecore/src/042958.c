/* GAMECORE.XFF @ 0x042958 (56 B) - SCRPlayableCharaTurnDirectInput
 * Evidence: `$f12` kept in `$f20`, `jal GetCharacterClass`, a 64-bit `ld` of
 * +0x7D8 OR-ed with 0x40000 and stored back, with `swc1 $f20,0x768`.
 * UNCONFIRMED: the class field meanings.
 
 */
struct CharacterClass {
    char pad[0x768];
    float turnInput;
    char pad7D8[0x6C];
    long flags7D8;
};

struct CharacterClass *GetCharacterClass(void);

void SCRPlayableCharaTurnDirectInput(float angle) {
    struct CharacterClass *c = GetCharacterClass();

    c->turnInput = angle;
    c->flags7D8 |= 0x40000;
}
