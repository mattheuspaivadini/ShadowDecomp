/* KERNEL.XFF @ 0x0051B0 (456 B) - iosNetRecvMsgWithStateCallback
 * Evidence: iosNetRecvMsg with a progress callback: after each chunk the buffer advances, a 0-byte read ends the loop and, when both the callback argument and the callback are set, cb(arg, received, len) is called. Inlined iosNetRecv copy. UNCONFIRMED: names.
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
int iosNetRecvMsgWithStateCallback(int fd, char *buf, int len, int flags, void *cbarg, void (*cb)(void *, int, int)) {
    int left = len;
    int n;

    while (left > 0) {
        n = iosNetRecv(fd, buf, left, flags);
        if (n < 0) {
            return n;
        }
        buf += n;
        if (n == 0) {
            break;
        }
        left -= n;
        if (cbarg != 0 && cb != 0) {
            cb(cbarg, len - left, len);
        }
    }
    return len - left;
}
