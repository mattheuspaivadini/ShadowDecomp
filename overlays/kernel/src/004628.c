/* KERNEL.XFF @ 0x004628 (376 B) - iosSendMsg
 * Evidence: message queue send under iosSystemSema: stores the message at buf[wpos] (8-byte slots), advances wpos modulo size and count; a waiting receiver (+0x14) is taken (a second one hits break 0) and woken through iosCallBackThreadMgr(.text+0x4990, thread) after the loop; a full queue in blocking mode (third argument 1) appends the current thread to the sender list (+0x18, link +0x28), sleeps and retries while the buffer still exists (goto loop: no loop-invariant hoisting). Returns 0 or -1. UNCONFIRMED: names.
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

int iosSendMsg(struct MsgQ *q, int msg, int block) {
    struct IosThread *self = iosGetThread();
    struct IosThread *wake = 0;
    struct IosThread *t;
    int ret;
    int pos;

retry:
    {
        WaitSema(iosSystemSema);
        if (q->count < q->size) {
            ret = 0;
            q->buf[q->wpos].data = msg;
            pos = q->wpos + 1;
            if (pos >= q->size) {
                pos = 0;
            }
            q->count++;
            q->wpos = pos;
            if (q->waiter != 0) {
                if (wake != 0) {
                    __asm__ __volatile__("break 0");
                }
                wake = q->waiter;
                q->waiter = 0;
            }
        } else {
            ret = -1;
        }
        if (ret != -1 || block != 1) {
            goto done;
        }
        t = q->sendq;
        self->next = 0;
        if (t != 0) {
            while (t->next != 0) {
                t = t->next;
            }
            t->next = self;
        } else {
            q->sendq = self;
        }
        SignalSema(iosSystemSema);
        iosSleepThread();
    }
    if (q->buf != 0) {
        goto retry;
    }
    return ret;
done:
    if (wake != 0) {
        iosCallBackThreadMgr(func_00004990, wake);
    }
    SignalSema(iosSystemSema);
    return ret;
}
