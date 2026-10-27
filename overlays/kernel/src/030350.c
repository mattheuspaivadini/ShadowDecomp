/* KERNEL.XFF @ 0x030350 (48 B) - Sg2StPcmSetVolume
 * Evidence: Sg2RemoteSend(0x22, a, b, 0); returns 0. UNCONFIRMED: Sg2RemoteSend command meaning.
 */
int Sg2RemoteSend(int cmd, int a, int b, int c);

int Sg2StPcmSetVolume(int a, int b) {
    Sg2RemoteSend(0x22, a, b, 0);
    return 0;
}
