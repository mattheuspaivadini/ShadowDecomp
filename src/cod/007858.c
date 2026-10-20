/* asm/cod/007858.s -> iWakeupThread.
 * SCE libkernl iWakeupThread: a different thread goes straight to the
 * _iWakeupThread syscall; waking the current thread (inline iGetThreadId
 * syscall, v1 = -0x2F) is queued on the request ring (cmd 0) for the
 * service thread, as in iRotateThreadReadyQueue.
 * MATCHED. */
struct Req07 { unsigned char cmd; unsigned char arg; };
struct Queue07 {
    int rd;                     /* 0x0 */
    int wr;                     /* 0x4 */
    struct Req07 req[0x200];    /* 0x8 */
};
extern int D_00132280 __attribute__((section(".data")));
extern int D_00143C90 __attribute__((section(".data")));
extern struct Queue07 D_00143C98;

void iSignalSema(int sema);
int _iWakeupThread(int tid);

static __inline__ int iGetThreadId(void) {
    register int v0 __asm__("$2");

    __asm__ __volatile__ ("addiu $3, $0, -0x2F
	syscall" : "=r" (v0) : : "$3");
    return v0;
}

int iWakeupThread(int tid) {
    unsigned int self;
    int n;

    self = iGetThreadId();
    if (self != tid)
        return _iWakeupThread(tid);
    if (self >= 0x100)
        return -1;
    if (D_00132280 == 0)
        return -1;
    n = D_00143C98.wr & 0x1FF;
    D_00143C98.wr = n + 1;
    D_00143C98.req[n].cmd = 0;
    D_00143C98.req[n].arg = self;
    iSignalSema(D_00143C90);
    return self;
}
