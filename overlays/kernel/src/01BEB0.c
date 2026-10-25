/* KERNEL.XFF @ 0x01BEB0 (64 B) - check_free_letter_post
 * Evidence: when *ppost is set: the static at .text+0x1BEF0 empties it, iosFree(*ppost) (reloaded), *ppost = 0. UNCONFIRMED: callee name.
 */
void func_01BEF0(void *post);
void iosFree(void *p);

void check_free_letter_post(void **ppost) {
    if (*ppost != 0) {
        func_01BEF0(*ppost);
        iosFree(*ppost);
        *ppost = 0;
    }
}
