/* KERNEL.XFF @ 0x01B5C8 (64 B) - iosAddISchedulerTaskList
 * Evidence: scans the three 8-byte {func, arg} slots at .bss+0x7A1F0 for an empty func and fills it (func, then arg); a full table hits `break 0` (an explicit trap asm). UNCONFIRMED: names.
 */
struct ISchedTask {
    void (*func)(void *);
    void *arg;
};
extern struct ISchedTask D_kernel_bss_7A1F0[3];

void iosAddISchedulerTaskList(void (*func)(void *), void *arg) {
    struct ISchedTask *t = D_kernel_bss_7A1F0;
    int i;

    for (i = 0; i < 3; i++, t++) {
        if (t->func == 0) {
            t->func = func;
            t->arg = arg;
            return;
        }
    }
    __asm__ __volatile__("break 0");
}
