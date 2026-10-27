/* KERNEL.XFF @ 0x0303C8 (44 B) - Sg2StPcmInit
 * Evidence: Sg2RemoteSend(0x1E, 0, 0, 0); returns 0. UNCONFIRMED: Sg2RemoteSend command meaning.
 */
int Sg2RemoteSend(int cmd, int a, int b, int c);

int Sg2StPcmInit(void) {
    Sg2RemoteSend(0x1E, 0, 0, 0);
    return 0;
}
