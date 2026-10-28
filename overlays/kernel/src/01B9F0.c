/* KERNEL.XFF @ 0x01B9F0 (308 B) - create_letter
 * Evidence: get_letter_type(id); the letter is iosMallocAlign(g_pLetterMem, type size (+4) + extra (+0x10) + 0x30, 0x10) with ref 1, id +0xC, type +0x10; the static .text+0x1BB58(letter, a, b, type) runs, the data pointer (+0x18) is the body at +0x30, the type's init callbacks (+8 on the data, +0x14 on the end pointer +0x1C) are called when present, +0x20 cleared and data/end returned through the first two arguments. UNCONFIRMED: names.
 */
struct LetterType {
    int unk0;
    int size;
    void (*init)(void *data);
    int unkC;
    int extra;
    void (*init2)(void *end);
};
struct Letter {
    int ref;
    int unk4;
    int unk8;
    int id;
    struct LetterType *type;
    int unk14;
    char *data;
    char *end;
    int unk20;
    char pad24[0xC];
    char body[1];
};
extern void *g_pLetterMem;
struct LetterType *get_letter_type(int id);
void *iosMallocAlign(void *ptn, int size, int align);
void func_01BB58(struct Letter *l, int a, int b, struct LetterType *t);

struct Letter *create_letter(char **pdata, char **pend, int id, int a, int b) {
    struct LetterType *t;
    struct Letter *l;

    t = get_letter_type(id);
    if (t != 0) {
        l = iosMallocAlign(g_pLetterMem, t->size + t->extra + 0x30, 0x10);
        if (l != 0) {
            l->id = id;
            l->ref = 1;
            l->unk4 = 0;
            l->unk8 = 0;
            l->type = t;
            func_01BB58(l, a, b, t);
            l->data = l->body;
            if (l->type->init != 0) {
                l->type->init(l->data);
            }
            l->end = l->data + l->type->size;
            if (l->type->init2 != 0) {
                l->type->init2(l->end);
            }
            l->unk20 = 0;
            *pdata = l->data;
            *pend = l->end;
            return l;
        }
    }
    return 0;
}
