/* KERNEL.XFF @ 0x01BF68 (16 B) - open_letter_post
 * Evidence: cur (+0xC) = 0, iterator (+0x10) = head (+4). UNCONFIRMED: names.
 */
struct LetterNode {
    void *letter;
    struct LetterNode *next;
};
struct LetterPost {
    int unk0;
    struct LetterNode *head;
    int unk8;
    struct LetterNode *cur;
    struct LetterNode *next;
};

void open_letter_post(struct LetterPost *post) {
    post->cur = 0;
    post->next = post->head;
}
