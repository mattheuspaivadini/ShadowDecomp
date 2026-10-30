/* GAMECORE.XFF @ 0x00C388 (28 B) - getFade
 * Evidence: a0=.data+0x650, sibling j checkFadeParam
 * UNCONFIRMED: none
 */
extern char D_kernel_data_0650[];
int checkFadeParam(char *p);

int getFade(void) {
    return checkFadeParam(D_kernel_data_0650);
}
