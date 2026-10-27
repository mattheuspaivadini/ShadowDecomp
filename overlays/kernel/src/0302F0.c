/* KERNEL.XFF @ 0x0302F0 (48 B) - Sg2StPcmStart
 * Evidence: Sg2RemoteSend(0x20, a, b, 0); returns 0. UNCONFIRMED: Sg2RemoteSend command meaning.
 */
int Sg2RemoteSend(int cmd, int a, int b, int c);

int Sg2StPcmStart(int a, int b) {
    Sg2RemoteSend(0x20, a, b, 0);
    return 0;
}
