/* KERNEL.XFF @ 0x0050C0 (240 B) - iosNetSend
 * Evidence: with the alternate driver flag (.data+0x260) sceInetSend(sock[fd].data, sock[fd].b, sock[fd].a, buf, len, &res, flags) on the 0x44-byte socket table at .bss+0xA370; otherwise fd and len go into the RPC buffer at .bss+0x9340, the payload is memcpy'd to +8 and sceSifCallRpc(.bss+0xA340, 3, 0, buf, len+8, buf, 4, 0, 0) runs under the semaphore at .bss+0xA368; the reply word is returned. UNCONFIRMED: names.
 */
struct NetBuf {
    int value;
    int size;
    char data[0x1000];
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
int sceInetSend(void *cd, int a, int b, void *buf, int len, int *res, int flags);

int iosNetSend(int fd, void *buf, int len, int flags) {
    int ret;
    int res;
    int ssize;

    if (D_kernel_data_0260) {
        res = 0;
        ret = sceInetSend(D_kernel_bss_A370[fd].data, D_kernel_bss_A370[fd].b, D_kernel_bss_A370[fd].a, buf, len, &res, flags);
    } else {
        ssize = len + 8;
        D_kernel_bss_9340.value = fd;
        D_kernel_bss_9340.size = len;
        memcpy(D_kernel_bss_9340.data, buf, len);
        WaitSema(D_kernel_bss_A368);
        sceSifCallRpc(D_kernel_bss_A340, 3, 0, &D_kernel_bss_9340, ssize, &D_kernel_bss_9340, 4, 0, 0);
        SignalSema(D_kernel_bss_A368);
        ret = D_kernel_bss_9340.value;
    }
    return ret;
}
