/* KERNEL.XFF @ 0x005410 (196 B) - iosNetOpen
 * Evidence: with the alternate driver flag (.data+0x260) forwards to the static at .text+0x49E8; otherwise copies strlen+1 bytes of the name after the length word at .bss+0x9340 and calls sceSifCallRpc(.bss+0xA340, 0, 0, buf, len+5, buf, 4, 0, 0) under the semaphore at .bss+0xA368, returning the reply word (sibling of iosNetClose). UNCONFIRMED: names.
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
unsigned int strlen(const char *s);
char *strncpy(char *d, const char *s, unsigned int n);
int func_0049E8(const char *name);
int iosNetOpen(const char *name) {
    int ret;
    int len;

    if (D_kernel_data_0260) {
        ret = func_0049E8(name);
    } else {
        len = strlen(name);
        D_kernel_bss_9340.value = len + 1;
        strncpy(D_kernel_bss_9340.name, name, len + 1);
        len += 5;
        WaitSema(D_kernel_bss_A368);
        sceSifCallRpc(D_kernel_bss_A340, 0, 0, &D_kernel_bss_9340, len, &D_kernel_bss_9340, 4, 0, 0);
        SignalSema(D_kernel_bss_A368);
        ret = D_kernel_bss_9340.value;
    }
    return ret;
}
