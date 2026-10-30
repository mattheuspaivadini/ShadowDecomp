/* GAMECORE.XFF @ 0x00C368 (32 B) - setFade
 * Evidence: a0=.data+0x650, a1=0x1B, sibling j setFadeParam
 * UNCONFIRMED: none
 */
extern char D_kernel_data_0650[];
void setFadeParam(char *p, int v);

void setFade(void) {
    setFadeParam(D_kernel_data_0650, 0x1B);
}
