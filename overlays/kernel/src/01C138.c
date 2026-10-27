/* KERNEL.XFF @ 0x01C138 (32 B) - constructor_letter_type
 * Evidence: kind (+0) = 2, words +4..+0x14 = 0 (the +0x14 store is emitted first by the scheduler). UNCONFIRMED: names.
 */
struct LetterType {
    int kind;
    int unk4;
    int unk8;
    int unkC;
    int unk10;
    int unk14;
};

void constructor_letter_type(struct LetterType *t) {
    t->kind = 2;
    t->unk4 = 0;
    t->unk8 = 0;
    t->unkC = 0;
    t->unk10 = 0;
    t->unk14 = 0;
}
