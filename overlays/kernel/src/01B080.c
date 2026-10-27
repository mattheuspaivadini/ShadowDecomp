/* KERNEL.XFF @ 0x01B080 (116 B) - isysObjWaitSema
 * Evidence: re-entrant object lock: when the owner (.data+0x7CC) is the current thread only the depth (.data+0x7D0) is incremented; otherwise WaitSema(.bss+0x7918C), owner = tid, depth = 1. UNCONFIRMED: names.
 */
extern int D_kernel_data_07CC;
extern int D_kernel_data_07D0;
extern int D_kernel_bss_7918C;
int GetThreadId(void);
int WaitSema(int sema);

void isysObjWaitSema(void) {
    int tid = GetThreadId();

    if (tid == D_kernel_data_07CC) {
        D_kernel_data_07D0++;
    } else {
        WaitSema(D_kernel_bss_7918C);
        D_kernel_data_07CC = tid;
        D_kernel_data_07D0 = 1;
    }
}
