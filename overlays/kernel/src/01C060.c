/* KERNEL.XFF @ 0x01C060 (212 B) - discard_selecting_letter_in_post
 * Evidence: unlinks the post's current node (+0xC): a single node resets count/head/tail/cur/iter; otherwise head, tail or middle unlink (new head/tail written back and then used to clear its link); decrement_letter_refcount(node), iosFree(node), cur = 0, count--. UNCONFIRMED: refcount argument (the node pointer is passed as in the image).
 */
struct LetterNode {
    void *letter;
    struct LetterNode *next;
    struct LetterNode *prev;
};
struct LetterPost {
    int count;
    struct LetterNode *head;
    struct LetterNode *tail;
    struct LetterNode *cur;
    struct LetterNode *iter;
};
void decrement_letter_refcount(void *letter);
void iosFree(void *p);

void discard_selecting_letter_in_post(struct LetterPost *post) {
    struct LetterNode *node = post->cur;

    if (node == 0) {
        return;
    }
    if (post->count == 1) {
        decrement_letter_refcount(node);
        iosFree(node);
        post->count = 0;
        post->head = 0;
        post->tail = 0;
        post->cur = 0;
        post->iter = 0;
        return;
    }
    if (node == post->head) {
        post->head = node->next;
        post->head->prev = 0;
    } else if (node == post->tail) {
        post->tail = node->prev;
        post->tail->next = 0;
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    node = post->cur;
    decrement_letter_refcount(node);
    iosFree(node);
    post->cur = 0;
    post->count--;
}
