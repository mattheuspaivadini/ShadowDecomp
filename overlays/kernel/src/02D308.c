/* KERNEL.XFF @ 0x02D308 (44 B) - Sg2StAdpcmClose
 * Evidence: Sg2RemoteSend(0x19, id, 0, 0); returns 0.
 */
int Sg2RemoteSend(int cmd, int a, int b, int c);

int Sg2StAdpcmClose(int id) {
    Sg2RemoteSend(0x19, id, 0, 0);
    return 0;
}
