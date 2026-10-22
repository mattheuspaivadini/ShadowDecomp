/* asm/cod/007A08.s -> DelayThread.
 * SCE libkernl DelayThread: refuses when interrupts are disabled (Status.EIE,
 * read with mfc0 $12), else sleeps on a one-shot semaphore that the timer
 * alarm handler func_00107C48 signals.
 * MATCHED. */
struct SemaParam {
    int count;              /* 0x00 */
    int max_count;          /* 0x04 */
    int init_count;         /* 0x08 */
    int wait_threads;       /* 0x0C */
    int attr;               /* 0x10 */
    char *option;           /* 0x14 */
};

extern char D_00137CC8[];   /* the semaphore name */

int CreateSema(struct SemaParam *param);
int DeleteSema(int sema);
int WaitSema(int sema);
unsigned long TimerUSec2BusClock(unsigned int sec, unsigned int usec);
int SetTimerAlarm(unsigned long clock, int (*handler)(int, int, int, int), void *arg);
int func_00107C48(int a0, int a1, int a2, int a3);   /* iSignalSema(a3); sync; ei */

int DelayThread(unsigned int usec) {
    struct SemaParam sp;
    int stat;
    int sema;
    int ret;

    __asm__ __volatile__ ("mfc0 %0, $12" : "=r" (stat));
    if (!(stat & 0x10000))
        return 0x80008008;
    sp.max_count = 1;
    sp.option = D_00137CC8;
    sp.init_count = 0;
    sema = CreateSema(&sp);
    if (sema < 0)
        return 0x80008003;
    ret = SetTimerAlarm(TimerUSec2BusClock(0, usec), func_00107C48, (void *)sema);
    if (ret < 0) {
        DeleteSema(sema);
        return ret;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return 0;
}
