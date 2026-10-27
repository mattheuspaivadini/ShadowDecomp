/* KERNEL.XFF @ 0x01EFD0 (100 B) - iosKeybdGetInfo
 * Evidence: WaitSema(.bss+0x7D440) then sceSifCallRpc(&cd .bss+0x7D448, 1, 1, send .bss+0x7D480, 0x20, buf, 0x20, the static end callback at .text+0x1EFB0, 0) and its result is returned (the callback signals the semaphore). UNCONFIRMED: names.
 */
extern int D_kernel_bss_7D440;
extern char D_kernel_bss_7D448[];
extern char D_kernel_bss_7D480[];
int WaitSema(int sema);
int sceSifCallRpc(void *cd, unsigned int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize,
                  void (*end)(void *), void *end_param);
void func_01EFB0(void *param);

int iosKeybdGetInfo(void *buf) {
    WaitSema(D_kernel_bss_7D440);
    return sceSifCallRpc(D_kernel_bss_7D448, 1, 1, D_kernel_bss_7D480, 0x20, buf, 0x20, func_01EFB0, 0);
}
