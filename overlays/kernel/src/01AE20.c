/* KERNEL.XFF @ 0x01AE20 (212 B) - isysGroupForExit
 * Evidence: the isysObjWaitSema body (nested lock: owner .data+0x7CC, depth .data+0x7D0, semaphore .bss+0x7918C), obj->ref-- (byte +9), then the isysObjSignalSema body ending in a sibling SignalSema; both helpers are inlined here (static inline copies of the lane functions 01B080/01B0F8). UNCONFIRMED: whether the source used inline functions or macros.
 */
struct IsysObj {
    char pad[9];
    unsigned char ref;
};
extern int D_kernel_data_07CC;
extern int D_kernel_data_07D0;
extern int D_kernel_bss_7918C;
int GetThreadId(void);
int WaitSema(int sema);
int SignalSema(int sema);

static inline void isysObjWaitSema(void) {
    int tid = GetThreadId();

    if (tid == D_kernel_data_07CC) {
        D_kernel_data_07D0++;
    } else {
        WaitSema(D_kernel_bss_7918C);
        D_kernel_data_07CC = tid;
        D_kernel_data_07D0 = 1;
    }
}

static inline void isysObjSignalSema(void) {
    if (--D_kernel_data_07D0 == 0) {
        D_kernel_data_07CC = -1;
        SignalSema(D_kernel_bss_7918C);
    }
}

void isysGroupForExit(struct IsysObj *obj) {
    isysObjWaitSema();
    obj->ref--;
    isysObjSignalSema();
}
