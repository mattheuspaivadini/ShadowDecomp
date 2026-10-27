/* KERNEL.XFF @ 0x006730 (96 B) - iosWakeupThread
 * Evidence: WakeupThread(t->id); a negative result jumps to iosJumpRecoverPoint(.rodata+0x8B0). the thread object comes from the argument or, when NULL, from the .bss+0xB1A0 table indexed by GetThreadId(); the kernel id is its word +4. UNCONFIRMED: struct layout beyond +4/+0x14.
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
int WakeupThread(int thid);
extern char D_kernel_rodata_08B0[];
void iosJumpRecoverPoint(const char *msg);

void iosWakeupThread(struct IosThread *t) {
    if (t == 0) {
        t = D_kernel_bss_B1A0[GetThreadId()];
    }
    if (WakeupThread(t->id) < 0) {
        iosJumpRecoverPoint(D_kernel_rodata_08B0);
    }
}
