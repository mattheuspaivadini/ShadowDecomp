/* KERNEL.XFF @ 0x0136C0 (112 B) - iosDlTrans
 * Evidence: WaitSema(volatile .bss+0x1EAD0); iosDmaSendSChainPath1(buf[workBufId == 0]); ++.data+0x564; sibling SignalSema. DL work block at .bss+0x1EAD8 (volatile struct). UNCONFIRMED: names.
 */
struct DLWork {
    char *base[2];
    char *buf[2];
    char *packet;
    int layerNum;
    int workBufId;
    int layer;
    char group[2][4];
    int lockNum[2];
};
extern volatile struct DLWork D_kernel_bss_1EAD8;
extern volatile int D_kernel_bss_1EAD0;
extern int D_kernel_data_0564;
int WaitSema(int sema);
int SignalSema(int sema);
void iosDmaSendSChainPath1(void *chain);

void iosDlTrans(void) {
    WaitSema(D_kernel_bss_1EAD0);
    iosDmaSendSChainPath1(D_kernel_bss_1EAD8.buf[D_kernel_bss_1EAD8.workBufId == 0]);
    D_kernel_data_0564++;
    SignalSema(D_kernel_bss_1EAD0);
}
