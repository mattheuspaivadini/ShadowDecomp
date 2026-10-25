/* KERNEL.XFF @ 0x0068A8 (96 B) - iosCallBackThreadMgr
 * Evidence: WaitSema(.bss+0xD5C4), then .bss+0xD5C0 = 1, +0xD5B8 = func, +0xD5BC = arg, and WakeupThread(word +4 of the thread object at .bss+0xD5B0). UNCONFIRMED: names (a callback request slot for a manager thread).
 */
struct IosThread {
    int unk0;
    int id;
    int unk8;
    int unkC;
    int unk10;
    int priority;
};
extern struct IosThread *D_kernel_bss_B1A0[];
int GetThreadId(void);
extern int D_kernel_bss_D5C4;
extern int D_kernel_bss_D5C0;
extern int D_kernel_bss_D5B8;
extern int D_kernel_bss_D5BC;
extern struct IosThread *D_kernel_bss_D5B0;
int WaitSema(int sema);
int WakeupThread(int thid);

void iosCallBackThreadMgr(int func, int arg) {
    WaitSema(D_kernel_bss_D5C4);
    D_kernel_bss_D5C0 = 1;
    D_kernel_bss_D5B8 = func;
    D_kernel_bss_D5BC = arg;
    WakeupThread(D_kernel_bss_D5B0->id);
}
