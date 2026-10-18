/* asm/cod/007690.s -> func_00107690.
 * libkernel request-thread loop; switch over the ring entry command (Session 22)
 * MATCHED. */
struct Req07 { unsigned char cmd; unsigned char arg; };
struct Queue07 {
    int rd;                     /* 0x0 */
    int wr;                     /* 0x4 */
    struct Req07 req[0x200];    /* 0x8 */
};
extern int D_00143C90 __attribute__((section(".data")));
extern char D_00137C88[];   /* "## internel error in libkernl.a!
" */

int  WaitSema(int sema);
int  WakeupThread(int tid);
int  RotateThreadReadyQueue(int prio);
int  SuspendThread(int tid);
int  kprintf(const char *fmt, ...);

void func_00107690(struct Queue07 *q) {
    int n;

    for (;;) {
        WaitSema(D_00143C90);
        n = q->rd & 0x1FF;
        q->rd = n + 1;
        switch (q->req[n].cmd) {
        case 0:
            WakeupThread(q->req[n].arg);
            break;
        case 1:
            RotateThreadReadyQueue(q->req[n].arg);
            break;
        case 2:
            SuspendThread(q->req[n].arg);
            break;
        default:
            kprintf(D_00137C88);
            break;
        }
    }
}
