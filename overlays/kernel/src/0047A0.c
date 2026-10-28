/* KERNEL.XFF @ 0x0047A0 (376 B) - iosRecvMsg
 * Evidence: message queue receive under iosSystemSema (a second receiver is reported with iosJumpRecoverPoint(.rodata+0x7A8)); the current thread is the receiver (+0x14); a message is read from buf[(wpos - count) mod size], count decremented and the first blocked sender is unlinked and woken (iosCallBackThreadMgr .text+0x4990); an empty queue in blocking mode sleeps and retries; a deleted queue (buf NULL) releases the whole sender list with .text+0x49A8. UNCONFIRMED: names.
 */
struct IosThread {
    char pad0[0x28];
    struct IosThread *next;
};
struct MsgEnt {
    int data;
    int pad;
};
struct MsgQ {
    struct MsgEnt *buf;
    int size;
    int count;
    int wpos;
    int rpos;
    struct IosThread *waiter;
    struct IosThread *sendq;
};
extern int iosSystemSema;
int WaitSema(int sema);
int SignalSema(int sema);
struct IosThread *iosGetThread(void);
void iosSleepThread(void);
void iosCallBackThreadMgr(void *func, void *arg);
void func_00004990(void);

extern char D_kernel_rodata_07A8[];
void iosJumpRecoverPoint(const char *fmt, ...);
void func_000049A8(void);

int iosRecvMsg(struct MsgQ *q, int *msg, int block) {
    struct IosThread *wake = 0;
    struct IosThread *list = 0;
    int ret;
    int pos;

    if (q->waiter != 0) {
        iosJumpRecoverPoint(D_kernel_rodata_07A8);
    }
retry:
    WaitSema(iosSystemSema);
    q->waiter = iosGetThread();
    if (q->buf != 0) {
        if (q->count != 0) {
            pos = q->wpos - q->count;
            pos = pos < 0 ? q->size + pos : pos;
            if (msg != 0) {
                *msg = q->buf[pos].data;
            }
            q->count--;
            ret = 0;
            if (q->sendq != 0) {
                wake = q->sendq;
                q->sendq = wake->next;
            }
        } else {
            ret = -1;
            if (block == 1) {
                SignalSema(iosSystemSema);
                iosSleepThread();
                goto retry;
            }
        }
    } else {
        list = q->sendq;
        ret = 0;
        q->sendq = 0;
    }
    q->waiter = 0;
    if (wake != 0) {
        iosCallBackThreadMgr(func_00004990, q->sendq);
    }
    if (list != 0) {
        iosCallBackThreadMgr(func_000049A8, list);
    }
    SignalSema(iosSystemSema);
    return ret;
}
