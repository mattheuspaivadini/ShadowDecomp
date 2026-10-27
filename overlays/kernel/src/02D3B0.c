/* KERNEL.XFF @ 0x02D3B0 (104 B) - Sg2StAdpcmSetPitch
 * Evidence: for pitch <= 0x2EE00 (192000, unsigned) and a non-zero voice mask: Sg2RemoteSend(0x1B, mask low 24, next 24, pitch), returns 0; otherwise -1.
 */
int Sg2RemoteSend(int cmd, int a, int b, int c);

int Sg2StAdpcmSetPitch(unsigned long voices, unsigned int pitch) {
    if (pitch <= 0x2EE00 && voices != 0) {
        Sg2RemoteSend(0x1B, voices & 0xFFFFFF, (voices >> 24) & 0xFFFFFF, pitch);
        return 0;
    }
    return -1;
}
