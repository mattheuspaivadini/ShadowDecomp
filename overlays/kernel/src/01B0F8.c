/* KERNEL.XFF @ 0x01B0F8 (76 B) - isysObjSignalSema
 * Evidence: --.data+0x7D0; when it reaches 0, .data+0x7CC = -1 and sibling SignalSema(.bss+0x7918C). UNCONFIRMED: names (a nested-lock owner/depth pair).
 */
extern int D_kernel_data_07D0;
extern int D_kernel_data_07CC;
extern int D_kernel_bss_7918C;
int SignalSema(int sema);

void isysObjSignalSema(void) {
    if (--D_kernel_data_07D0 == 0) {
        D_kernel_data_07CC = -1;
        SignalSema(D_kernel_bss_7918C);
    }
}
