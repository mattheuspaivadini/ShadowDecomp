/* KERNEL.XFF @ 0x01B940 (176 B) - isysLetterObjDiscardLetterAll
 * Evidence: inlined isysGetLetterObj (types 6, 9, 11, 13, 22; jump tables at .rodata+0x2580 / +0x25D0 read from the container) twice: for a letter object, open_letter_post, discard_all_letter_in_post and close_letter_post (tail) on its post (+0x1C). UNCONFIRMED: field name.
 */
struct LetterPost;
struct IsysObj {
    char pad[8];
    unsigned char type;
    char pad9[0x1C - 9];
    struct LetterPost *post;
};
void open_letter_post(struct LetterPost *post);
void discard_all_letter_in_post(struct LetterPost *post);
void close_letter_post(struct LetterPost *post);

static __inline__ struct IsysObj *isysGetLetterObj(struct IsysObj *obj) {
    switch (obj->type) {
    case 6:
    case 9:
    case 11:
    case 13:
    case 22:
        return obj;
    }
    return 0;
}

void isysLetterObjDiscardLetterAll(struct IsysObj *obj) {
    struct LetterPost *post;

    if (isysGetLetterObj(obj)) {
        post = isysGetLetterObj(obj)->post;
        open_letter_post(post);
        discard_all_letter_in_post(post);
        close_letter_post(post);
    }
}
