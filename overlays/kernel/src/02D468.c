/* KERNEL.XFF @ 0x02D468 (80 B) - Sg2StAdpcmStop
 * Evidence: for a non-zero 48-bit voice mask, Sg2RemoteSend(0x1D, low 24 bits, next 24 bits, 0); returns 0.
 */
int Sg2RemoteSend(int cmd, int a, int b, int c);

int Sg2StAdpcmStop(unsigned long voices) {
    if (voices != 0) {
        Sg2RemoteSend(0x1D, voices & 0xFFFFFF, (voices >> 24) & 0xFFFFFF, 0);
    }
    return 0;
}
