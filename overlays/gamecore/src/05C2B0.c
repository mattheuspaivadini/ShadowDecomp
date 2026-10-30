/* GAMECORE.XFF @ 0x05C2B0 (48 B) - SCRConditionHorseRiddenOn
 * Evidence: `$a0` saved in `$s0`, `jal GetCharacterClass`, then
 * `xor $s0,$s0,$v1` against `0x960($v0)` and `sltu $v0,$zero,$s0`
 * (a `!=` compare).
 * UNCONFIRMED: the class field meaning.
 
 */
struct CharacterClass {
    char pad[0x960];
    int f960;
};

struct CharacterClass *GetCharacterClass(void);

int SCRConditionHorseRiddenOn(int value) {
    return value != GetCharacterClass()->f960;
}
