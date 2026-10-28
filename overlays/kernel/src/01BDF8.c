/* KERNEL.XFF @ 0x01BDF8 (120 B) - func_01BDF8 (static, no symbol in the shipped .symtab)
 * Evidence: a letter goes into the object post (+0x1C, push_back_letter_in_post) and 1 is returned when the receiver has no filter (+0xC) or the filter (obj, get_letter_receiver_data(letter)) returns 1; else 0. UNCONFIRMED: names; Ghidra FUN_0021bdf8.
 */
struct LetterPost;
struct LetterObj {
    char pad[0x1C];
    struct LetterPost *post;
};
struct LetterReceiver {
    char pad[0xC];
    int (*func)(struct LetterObj *obj, void *data);
};
void *get_letter_receiver_data(void *letter);
void push_back_letter_in_post(struct LetterPost *post, void *letter);

int func_01BDF8(struct LetterObj *obj, void *letter, struct LetterReceiver *r) {
    if (r->func == 0 || r->func(obj, get_letter_receiver_data(letter)) == 1) {
        push_back_letter_in_post(obj->post, letter);
        return 1;
    }
    return 0;
}
