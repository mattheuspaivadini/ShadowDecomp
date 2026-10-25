/* KERNEL.XFF @ 0x0303F8 (44 B) - Sg2StPcmQuit
 * Evidence: Sg2RemoteSend(0x1F, 0, 0, 0); returns 0. UNCONFIRMED: Sg2RemoteSend command meaning.
 */
int Sg2RemoteSend(int cmd, int a, int b, int c);

int Sg2StPcmQuit(void) {
    Sg2RemoteSend(0x1F, 0, 0, 0);
    return 0;
}
