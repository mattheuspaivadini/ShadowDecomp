/* KERNEL.XFF @ 0x0066C8 (76 B) - iosStartThread
 * Evidence: sibling StartThread(t->id, arg); the thread object comes from the argument or, when NULL, from the .bss+0xB1A0 table indexed by GetThreadId(); the kernel id is its word +4. UNCONFIRMED: struct layout beyond +4/+0x14.
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
int StartThread(int thid, void *arg);

void iosStartThread(struct IosThread *t, void *arg) {
    if (t == 0) {
        t = D_kernel_bss_B1A0[GetThreadId()];
    }
    StartThread(t->id, arg);
}
