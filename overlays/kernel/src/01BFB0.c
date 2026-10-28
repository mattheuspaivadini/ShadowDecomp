/* KERNEL.XFF @ 0x01BFB0 (24 B) - func_01BFB0 (static, no symbol in the shipped .symtab)
 * Evidence: letter post initialiser called by create_letter_post: count, head, tail, cur and iterator cleared.
 */
struct LetterNode;
struct LetterPost {
    int count;
    struct LetterNode *head;
    struct LetterNode *tail;
    struct LetterNode *cur;
    struct LetterNode *iter;
};

void func_01BFB0(struct LetterPost *post) {
    post->count = 0;
    post->head = 0;
    post->tail = 0;
    post->cur = 0;
    post->iter = 0;
}
