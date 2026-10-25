/* KERNEL.XFF @ 0x01BE70 (64 B) - create_letter_post
 * Evidence: iosMallocAlign(g_pLetterMem, 0x14, 0x10), initialised by the static at .text+0x1BFB0, returned. UNCONFIRMED: callee name.
 */
extern void *g_pLetterMem;
void *iosMallocAlign(void *ptn, int size, int align);
void func_01BFB0(void *post);

void *create_letter_post(void) {
    void *post = iosMallocAlign(g_pLetterMem, 0x14, 0x10);

    func_01BFB0(post);
    return post;
}
