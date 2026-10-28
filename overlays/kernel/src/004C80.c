/* KERNEL.XFF @ 0x004C80 (420 B) - iosNetRecvMsg
 * Evidence: receive loop around an inlined copy of iosNetRecv (driver flag .data+0x260, sceInetRecv on the socket table .bss+0xA370 or the RPC buffer .bss+0x9340 under the semaphore .bss+0xA368): reads until len bytes arrived, returns a negative result immediately, stops on 0 and returns the received count (result kept in a variable with a goto to the common return). UNCONFIRMED: names.
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

static __inline__ int iosNetRecv(int fd, void *buf, int len, int flags) {
    int ret;
    struct NetBuf *nb = &D_kernel_bss_9340;
    int res;
    int n;
    int rsize;
    int *p;

    if (D_kernel_data_0260) {
        res = 0;
        return sceInetRecv(D_kernel_bss_A370[fd].data, D_kernel_bss_A370[fd].b, D_kernel_bss_A370[fd].a, buf,
                           len < 0x701 ? len : 0x700, &res, flags);
    }
    n = len < 0xF01 ? len : 0xF00;
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
int iosNetRecvMsg(int fd, char *buf, int len, int flags) {
    int left = len;
    int n;
    int ret;

    while (left > 0) {
        n = iosNetRecv(fd, buf, left, flags);
        if (n < 0) {
            ret = n;
            goto out;
        }
        if (n == 0) {
            break;
        }
        left -= n;
        buf += n;
    }
    ret = len - left;
out:
    return ret;
}
