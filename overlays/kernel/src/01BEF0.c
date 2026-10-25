/* KERNEL.XFF @ 0x01BEF0 (112 B) - discard_all_letter_in_post
 * Evidence: frees every node of the post list (decrement_letter_refcount(&node->letter), iosFree(node), next read first), then clears +0x10, +0, +4, +8, +0xC (source order 0..0x10; the last store is emitted first).
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
int decrement_letter_refcount(void **pref);
void iosFree(void *p);

void discard_all_letter_in_post(struct LetterPost *post) {
    struct LetterNode *n;
    struct LetterNode *next;

    for (n = post->head; n != 0; n = next) {
        next = n->next;
        decrement_letter_refcount(&n->letter);
        iosFree(n);
    }
    post->unk0 = 0;
    post->head = 0;
    post->unk8 = 0;
    post->cur = 0;
    post->next = 0;
}
