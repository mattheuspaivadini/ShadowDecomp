/* KERNEL.XFF @ 0x013B10 (92 B) - iosDlTransNow
 * Evidence: WaitSema(volatile .bss+0x1EAD0); iosDmaSendSChainPath1(buf[workBufId == 0]); sibling SignalSema. DL work block at .bss+0x1EAD8 (volatile struct, see iosDlGetLayer). UNCONFIRMED: names.
 */
struct DLWork {
    char *base[2];
    char *buf[2];
    char *packet;
    int layerNum;
    int workBufId;
    int layer;
};
extern volatile struct DLWork D_kernel_bss_1EAD8;
extern volatile int D_kernel_bss_1EAD0;
int WaitSema(int sema);
int SignalSema(int sema);
void iosDmaSendSChainPath1(void *chain);

void iosDlTransNow(void) {
    WaitSema(D_kernel_bss_1EAD0);
    iosDmaSendSChainPath1(D_kernel_bss_1EAD8.buf[D_kernel_bss_1EAD8.workBufId == 0]);
    SignalSema(D_kernel_bss_1EAD0);
}
