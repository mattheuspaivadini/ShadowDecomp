/* KERNEL.XFF @ 0x020538 (12 B) - Sg2ExStAdpcmSetFd
 * Evidence: stores fd at +0x2D8 and returns 0.
 */
struct ExStAdpcm {
    char pad[0x2D8];
    int fd;
};

int Sg2ExStAdpcmSetFd(struct ExStAdpcm *w, int fd) {
    w->fd = fd;
    return 0;
}
