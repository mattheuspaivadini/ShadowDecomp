/* KERNEL.XFF @ 0x006830 (116 B) - iosDeleteThread
 * Evidence: WaitSema(.bss+0xD5C4); the thread (or the current one via the .bss+0xB1A0 table) goes to .bss+0xD5B4, .bss+0xD5C0 = 0, and the manager thread (.bss+0xD5B0, id at +4) is woken. UNCONFIRMED: names (delete request to the thread manager).
 */
struct IosThread {
    int unk0;
    int id;
};
extern struct IosThread *D_kernel_bss_B1A0[];
extern int D_kernel_bss_D5C4;
extern int D_kernel_bss_D5C0;
extern struct IosThread *D_kernel_bss_D5B4;
extern struct IosThread *D_kernel_bss_D5B0;
int GetThreadId(void);
int WaitSema(int sema);
int WakeupThread(int thid);

void iosDeleteThread(struct IosThread *t) {
    WaitSema(D_kernel_bss_D5C4);
    if (t == 0) {
        t = D_kernel_bss_B1A0[GetThreadId()];
    }
    D_kernel_bss_D5C0 = 0;
    D_kernel_bss_D5B4 = t;
    WakeupThread(D_kernel_bss_D5B0->id);
}
