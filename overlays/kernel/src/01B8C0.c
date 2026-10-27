/* KERNEL.XFF @ 0x01B8C0 (40 B) - isysInitISYSLetterObj
 * Evidence: obj->+0x1C = create_letter_post(). UNCONFIRMED: field name.
 */
struct LetterObj {
    char pad[0x1C];
    void *post;
};
void *create_letter_post(void);

void isysInitISYSLetterObj(struct LetterObj *obj) {
    obj->post = create_letter_post();
}
