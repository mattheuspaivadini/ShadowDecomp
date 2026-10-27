/* KERNEL.XFF @ 0x02D4D0 (44 B) - Sg2StAdpcmInit
 * Evidence: Sg2RemoteSend(0x16, 0, 0, 0); returns 0.
 */
int Sg2RemoteSend(int cmd, int a, int b, int c);

int Sg2StAdpcmInit(void) {
    Sg2RemoteSend(0x16, 0, 0, 0);
    return 0;
}
