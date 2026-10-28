/* KERNEL.XFF @ 0x01BFC8 (148 B) - push_back_letter_in_post
 * Evidence: a 0xC-byte node {letter, next, prev} from iosMallocAlign(g_pLetterMem, 0xC, 0x10); increment_letter_refcount(letter); appended to the post (count +0, head +4, tail +8; empty post: head then tail written); count++.
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
extern void *g_pLetterMem;
void *iosMallocAlign(void *ptn, int size, int align);
void increment_letter_refcount(void *letter);
void push_back_letter_in_post(struct LetterPost *post, void *letter) {
    struct LetterNode *node = iosMallocAlign(g_pLetterMem, 0xC, 0x10);
    node->letter = letter;
    node->next = 0;
    increment_letter_refcount(letter);
 if (post->count == 0) { node->prev = 0; post->head = node; post->tail = node; }
 else { node->prev = post->tail; post->tail->next = node; post->tail = node; }
 post->count++;
}
