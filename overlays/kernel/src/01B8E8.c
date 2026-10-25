/* KERNEL.XFF @ 0x01B8E8 (24 B) - isysFlushISYSLetterObj
 * Evidence: sibling check_free_letter_post(&obj->+0x1C).
 */
struct LetterObj {
    char pad[0x1C];
    void *post;
};
void check_free_letter_post(void **post);

void isysFlushISYSLetterObj(struct LetterObj *obj) {
    check_free_letter_post(&obj->post);
}
