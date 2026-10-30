/* GAMECORE.XFF @ 0x00C478 (28 B) - getDemoBar
 * Evidence: a0=.data+0x668, sibling j checkFadeParam
 * UNCONFIRMED: none
 */
extern char D_kernel_data_0668[];
int checkFadeParam(char *p);

int getDemoBar(void) {
    return checkFadeParam(D_kernel_data_0668);
}
