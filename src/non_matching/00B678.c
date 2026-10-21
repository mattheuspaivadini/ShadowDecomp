/* STATUS (Session 42, 2026-10-21): NON_MATCHING. best score 16 (was 22; sw.py diff lines).
 * Fence grid (build/s42/fence_grid.py: empty asm "+r" / asm volatile "r" use of each local after each statement): best single fence of 1274; a second-level grid (on top of it) gave no further gain. sceRead-template fences (m operands on _sceFs_q/D_00146600) without the nowait pin: 44-58.
 * sceWrite: unaligned head (16 - buf & 15, written as (aligned + 16) - buf to keep the srl/sll +
 * subu shape) copied into the request, rest by DMA. nowait pinned to s4. Residuals: i = 0 vs
 * nowait copy (sceLseek class), async coalesces into s4 with the pin, and the head-copy loop swaps
 * a1/a2 (index vs request base).
 * The original .s stays in the build (asm/cod/00B678.s); this C
 * draft (Session 36) is kept for the record. */
struct Fd {                     /* 16-byte EE fd records at D_00146EC0 */
    int iop_fd;                 /* 0x00 */
    int mode;                   /* 0x04 */
    int f08;
    int f0C;
};

struct SemaParam {
    int count;                  /* 0x00 */
    int max_count;              /* 0x04 */
    int init_count;             /* 0x08 */
    int wait_threads;           /* 0x0C */
    int attr;                   /* 0x10 */
    char *option;               /* 0x14 */
};

struct Req {                    /* the send buffer at D_001459C0 */
    int sema;                   /* 0x00 */
    int *ret;                   /* 0x04 */
    int ret_size;               /* 0x08 */
    int iop_fd;                 /* 0x0C */
    void *buf;                  /* 0x10 */
    int size;                   /* 0x14 */
    int head;                   /* 0x18 */
    char data[16];              /* 0x1C: the unaligned head of buf */
    int fd;                     /* 0x2C */
};

extern int D_00132314 __attribute__((section(".data")));
extern int D_00132324 __attribute__((section(".data")));
extern struct Req D_001459C0;
extern struct Fd D_00146EC0[];
extern int D_00146600[];
extern int D_001470C0[];
extern int _sceFs_q[32];
extern char D_00137FE0[];

struct Fd *func_0010A318(int fd);
int func_0010A798(int a0);
int func_0010A7C8(void);
int func_0010A228(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8, int a9);
int CreateSema(struct SemaParam *param);
int DeleteSema(int sema);
int WaitSema(int sema);
int SignalSema(int sema);
void sceSifWriteBackDCache(void *addr, int size);

int sceWrite(int fd, void *buf, int size) {
    struct Req *req = &D_001459C0;
    struct Fd *f;
    struct SemaParam sp;
    int ret[4];
    int mode;
    register int nowait asm("$20");
    int async;
    int sema;
    int st;
    int i;
    int head;

    f = func_0010A318(fd);
    func_0010A798(3);
    if (D_00132314 == 0 || f == 0 || (mode = f->mode) == 0) {
        func_0010A7C8();
        return -9;
    }
    req->iop_fd = f->iop_fd;
    req->fd = f - D_00146EC0;
    sp.max_count = 1;
    sp.option = D_00137FE0;
    req->size = size;
    req->buf = buf;
    sp.init_count = 0;
    async = mode & 0x8000;
    sema = CreateSema(&sp);
    req->ret = ret;
    req->ret_size = 4;
    req->sema = sema;
    if (async) {
        WaitSema(D_00132324);
        __asm__ __volatile__ ("" : "+r" (async));
        i = 0;
        asm volatile("" : : "r"(nowait));
        nowait = async;
        for (; i < 32; i++) {
            if (_sceFs_q[i] == -1) {
                _sceFs_q[i] = req->sema;
                req->sema = -req->sema;
                break;
            }
        }
        SignalSema(D_00132324);
    } else {
        nowait = 0;
    }
    if (((unsigned int)buf & 0xF) == 0)
        head = 0;
    else
        head = (int)((char *)((((unsigned int)buf >> 4) << 4) + 16) - (char *)buf);
    if (size < head)
        head = size;
    if (!(mode & 0x20000000))
        sceSifWriteBackDCache(buf, size);
    buf = (void *)((unsigned int)buf | 0x20000000);
    req->head = head;
    for (i = 0; i < head; i++)
        req->data[i] = ((char *)buf)[i];
    if (func_0010A228((int)D_001470C0, 3, 0, (int)&D_001459C0, 0x30, (int)D_00146600, 4, 0, 0, nowait) < 0) {
        DeleteSema(sema);
        func_0010A7C8();
        return -0xB;
    }
    st = *(int *)((unsigned int)D_00146600 | 0x20000000);
    func_0010A7C8();
    if (st == 0) {
        DeleteSema(sema);
        return -0xB;
    }
    if (nowait) {
        DeleteSema(sema);
        return 0;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return ret[0];
}
