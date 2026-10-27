/* KERNEL.XFF @ 0x0067A8 (72 B) - iosChangeThreadPriority
 * Evidence: stores the priority to +0x14; the thread object comes from the argument or, when NULL, from the .bss+0xB1A0 table indexed by GetThreadId(); the kernel id is its word +4. UNCONFIRMED: struct layout beyond +4/+0x14.
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
void iosChangeThreadPriority(struct IosThread *t, int prio) {
    if (t == 0) {
        t = D_kernel_bss_B1A0[GetThreadId()];
    }
    t->priority = prio;
}
