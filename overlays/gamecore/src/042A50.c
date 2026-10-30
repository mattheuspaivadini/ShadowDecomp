/* GAMECORE.XFF @ 0x042A50 (48 B) - SCRCharaStand
 * Evidence: `jal GetCharacterClass` then five zero word stores at
 * +0x814, +0x7E4, +0x7EC, +0x81C, +0x818.
 * UNCONFIRMED: the class field meanings.
 
 */
struct CharacterClass {
    char pad7E4[0x7E4];
    int f7E4;
    int f7E8;
    int f7EC;
    char pad814[0x24];
    int f814;
    int f818;
    int f81C;
};

struct CharacterClass *GetCharacterClass(void);

void SCRCharaStand(void) {
    struct CharacterClass *c = GetCharacterClass();

    c->f7E4 = 0;
    c->f7EC = 0;
    c->f81C = 0;
    c->f818 = 0;
    c->f814 = 0;
}
