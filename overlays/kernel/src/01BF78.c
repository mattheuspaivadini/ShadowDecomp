/* KERNEL.XFF @ 0x01BF78 (36 B) - get_next_letter_in_post
 * Evidence: `lw v1,0x10(a0)` = p->pending; `beql v1,zero` with the annulled
 * `daddu v1,zero,zero` initialises the returned value in the null case;
 * otherwise p->current (+0xC) = node, v0 = node->next (+0x4) is stored back to
 * +0x10 and the value (+0x0) is returned (`daddu v0,v1,zero` in the jr slot).
 * The explicit `else { value = 0; }` (rather than `value = 0` before the if) is
 * what makes 2.96 emit the `beql` + shared $v1 pseudo; -fno-strict-aliasing is
 * required.
 * UNCONFIRMED: struct/field names, the meaning of the 3 leading ints.
 */
typedef struct PostNode {
    int value;
    struct PostNode *next;
} PostNode;

typedef struct Post {
    int pad[3];
    PostNode *current;
    PostNode *pending;
} Post;

int get_next_letter_in_post(Post *p) {
    PostNode *node = p->pending;
    int value;

    if (node != 0) {
        p->current = node;
        value = node->value;
        p->pending = node->next;
    } else {
        value = 0;
    }
    return value;
}
