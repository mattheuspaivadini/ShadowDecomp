/* KERNEL.XFF @ 0x02D338 (120 B) - Sg2StAdpcmSetVolume
 * Evidence: for l < 0x4000 (unsigned), 0 <= r < 0x4000 and a non-zero voice mask: Sg2RemoteSend(0x1A, mask low 24 bits, next 24 bits, l << 16 | r), returns 0; otherwise -1.
 */
int Sg2RemoteSend(int cmd, int a, int b, int c);

int Sg2StAdpcmSetVolume(unsigned long voices, unsigned int l, int r) {
    if (l < 0x4000 && r >= 0 && r < 0x4000 && voices != 0) {
        Sg2RemoteSend(0x1A, voices & 0xFFFFFF, (voices >> 24) & 0xFFFFFF, (l << 16) | r);
        return 0;
    }
    return -1;
}
