/* KERNEL.XFF @ 0x02D418 (80 B) - Sg2StAdpcmPlay
 * Evidence: for a non-zero 48-bit voice mask, Sg2RemoteSend(0x1C, low 24 bits, next 24 bits, 0) (both sign-extended to int); returns 0.
 */
int Sg2RemoteSend(int cmd, int a, int b, int c);

int Sg2StAdpcmPlay(unsigned long voices) {
    if (voices != 0) {
        Sg2RemoteSend(0x1C, voices & 0xFFFFFF, (voices >> 24) & 0xFFFFFF, 0);
    }
    return 0;
}
