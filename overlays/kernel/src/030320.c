/* KERNEL.XFF @ 0x030320 (44 B) - Sg2StPcmStop
 * Evidence: Sg2RemoteSend(0x21, 0, 0, 0); returns 0. UNCONFIRMED: Sg2RemoteSend command meaning.
 */
int Sg2RemoteSend(int cmd, int a, int b, int c);

int Sg2StPcmStop(void) {
    Sg2RemoteSend(0x21, 0, 0, 0);
    return 0;
}
