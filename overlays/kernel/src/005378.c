/* KERNEL.XFF @ 0x005378 (152 B) - iosNetClose
 * Evidence: with the alternate driver flag (.data+0x260) the static at .text+0x4BF8 handles (fd, -1); otherwise the fd goes into the RPC buffer at .bss+0x9340 and sceSifCallRpc(&cd .bss+0xA340, 1, 0, buf, 4, buf, 4, 0, 0) runs under the semaphore at .bss+0xA368; the reply word is returned (result kept in a variable: no sibling call). UNCONFIRMED: names.
 */
struct NetBuf {
    int value;
    char name[0x100];
};
extern int D_kernel_data_0260;
extern struct NetBuf D_kernel_bss_9340;
extern char D_kernel_bss_A340[];
extern int D_kernel_bss_A368;
int WaitSema(int sema);
int SignalSema(int sema);
int sceSifCallRpc(void *cd, unsigned int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize,
                  void (*end)(void *), void *end_param);
int func_004BF8(int fd, int a);

int iosNetClose(int fd) {
    int ret;

    if (D_kernel_data_0260) {
        ret = func_004BF8(fd, -1);
    } else {
        D_kernel_bss_9340.value = fd;
        WaitSema(D_kernel_bss_A368);
        sceSifCallRpc(D_kernel_bss_A340, 1, 0, &D_kernel_bss_9340, 4, &D_kernel_bss_9340, 4, 0, 0);
        SignalSema(D_kernel_bss_A368);
        ret = D_kernel_bss_9340.value;
    }
    return ret;
}
