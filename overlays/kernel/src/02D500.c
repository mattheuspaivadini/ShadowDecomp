/* KERNEL.XFF @ 0x02D500 (44 B) - Sg2StAdpcmQuit
 * Evidence: Sg2RemoteSend(0x17, 0, 0, 0); returns 0.
 */
int Sg2RemoteSend(int cmd, int a, int b, int c);

int Sg2StAdpcmQuit(void) {
    Sg2RemoteSend(0x17, 0, 0, 0);
    return 0;
}
