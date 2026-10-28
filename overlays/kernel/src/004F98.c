/* KERNEL.XFF @ 0x004F98 (296 B) - iosNetRecv
 * Evidence: with the alternate driver flag (.data+0x260) sceInetRecv(sock[fd].data, sock[fd].b, sock[fd].a, buf, min(len, 0x700), &res, flags); otherwise len is clamped to 0xF00, fd/len go into the RPC buffer at .bss+0x9340, sceSifCallRpc(.bss+0xA340, 2, 0, buf, 8, buf, len+4, 0, 0) under the semaphore at .bss+0xA368, and the reply word is returned after memcpy(buf, rpc+4, len). Register-pinned locals reproduce the s-register roles. UNCONFIRMED: names.
 */
struct NetBuf {
    int value;
    int size;
    char data[0xF00];
};
struct NetSock {
    int a;
    int b;
    char data[0x3C];
};
extern int D_kernel_data_0260;
extern struct NetBuf D_kernel_bss_9340;
extern char D_kernel_bss_A340[];
extern int D_kernel_bss_A368;
extern struct NetSock D_kernel_bss_A370[];
int WaitSema(int sema);
int SignalSema(int sema);
int sceSifCallRpc(void *cd, unsigned int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize,
                  void (*end)(void *), void *end_param);
void *memcpy(void *d, const void *s, unsigned int n);
int sceInetRecv(void *cd, int a, int b, void *buf, int len, int *res, int flags);

int iosNetRecv(int fd, void *buf, int len, int flags) {
    int ret;
    int res;
    register int n asm("$17");
    register struct NetBuf *nb asm("$16");
    int rsize;
    register int *p asm("$20");

    if (D_kernel_data_0260) {
        res = 0;
        return sceInetRecv(D_kernel_bss_A370[fd].data, D_kernel_bss_A370[fd].b, D_kernel_bss_A370[fd].a, buf,
                           len < 0x701 ? len : 0x700, &res, flags);
    }
    n = len < 0xF01 ? len : 0xF00;
    nb = &D_kernel_bss_9340;
    p = &nb->size;
    nb->value = fd;
    *p = n;
    rsize = n + 4;
    WaitSema(D_kernel_bss_A368);
    sceSifCallRpc(D_kernel_bss_A340, 2, 0, nb, 8, nb, rsize, 0, 0);
    SignalSema(D_kernel_bss_A368);
    ret = nb->value;
    memcpy(buf, p, n);
    return ret;
}
