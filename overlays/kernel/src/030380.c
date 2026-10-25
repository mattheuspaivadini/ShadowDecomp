/* KERNEL.XFF @ 0x030380 (44 B) - Sg2StPcmSetEffect
 * Evidence: Sg2RemoteSend(0x23, a, 0, 0); returns 0. UNCONFIRMED: Sg2RemoteSend command meaning.
 */
int Sg2RemoteSend(int cmd, int a, int b, int c);

int Sg2StPcmSetEffect(int a) {
    Sg2RemoteSend(0x23, a, 0, 0);
    return 0;
}
