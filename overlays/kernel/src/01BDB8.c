/* KERNEL.XFF @ 0x01BDB8 (60 B) - send_letter
 * Evidence: push_back_letter_in_post(post at .bss+0x7C210, *pref); decrement_letter_refcount(pref); *pref = 0.
 */
extern void *D_kernel_bss_7C210;
void push_back_letter_in_post(void *post, void *letter);
int decrement_letter_refcount(void **pref);

void send_letter(void **pref) {
    push_back_letter_in_post(D_kernel_bss_7C210, *pref);
    decrement_letter_refcount(pref);
    *pref = 0;
}
