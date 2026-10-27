/* KERNEL.XFF @ 0x01BFA0 (12 B) - close_letter_post
 * Evidence: clears +0x10 and +0xC (source order cur then next; the scheduler emits the last independent store first).
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

void close_letter_post(struct LetterPost *post) {
    post->cur = 0;
    post->next = 0;
}
