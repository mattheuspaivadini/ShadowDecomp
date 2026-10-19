/* STATUS (Session 34, 2026-10-19): NON_MATCHING. best score 7 [cc=29].
 * sceRead (sceIoctl2 template). req local, RPC call with &D_001459C0, async = mode & 0x8000 before
 * CreateSema, nowait = 0 in the else, ret before ret_size, sema pinned to s3. Residual = the nowait =
 * async copy: the original has it after WaitSema (delay slot of the q[0] test), sched1 moves ours
 * above the call.
 * Tried: copy placed after WaitSema / after i = 0 / after SignalSema (608-612 bytes), empty asm with
 * +r on async (volatile keeps 7, non-volatile 16), nowait pinned to s2.
 * The original .s stays in the build (asm/cod/00B408.s); this C
 * draft (Session 34) is kept for the record. */
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
    int f18;                    /* 0x18 */
    int fd;                     /* 0x1C */
};

extern int D_00132314 __attribute__((section(".data")));
extern int D_00132324 __attribute__((section(".data")));
extern struct Req D_001459C0;
extern struct Fd D_00146EC0[];
extern int D_00146600[];
extern int D_001470C0[];
extern int _sceFs_q[32];
extern char D_00137FC8[];

struct Fd *func_0010A318(int fd);
int func_0010A798(int a0);
int func_0010A7C8(void);
int func_0010A228(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8, int a9);
void sceSifWriteBackDCache(void *addr, int size);
int CreateSema(struct SemaParam *param);
int DeleteSema(int sema);
int WaitSema(int sema);
int SignalSema(int sema);

int sceRead(int fd, void *buf, int size) {
    struct Req *req = &D_001459C0;
    struct Fd *f;
    struct SemaParam sp;
    int ret[4];
    int mode;
    int nowait;
    int async;
    register int sema asm("$19");
    int st;
    int i;

    f = func_0010A318(fd);
    func_0010A798(2);
    if (D_00132314 == 0 || f == 0 || (mode = f->mode) == 0) {
        func_0010A7C8();
        return -9;
    }
    req->iop_fd = f->iop_fd;
    req->fd = f - D_00146EC0;
    sp.max_count = 1;
    sp.option = D_00137FC8;
    req->buf = buf;
    req->size = size;
    sp.init_count = 0;
    async = mode & 0x8000;
    sema = CreateSema(&sp);
    req->ret = ret;
    req->ret_size = 4;
    req->sema = sema;
    if (async) {
        nowait = async;
        WaitSema(D_00132324);
        for (i = 0; i < 32; i++) {
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
    if (!(mode & 0x20000000))
        sceSifWriteBackDCache(buf, size);
    sceSifWriteBackDCache(req, 0x20);
    if (func_0010A228((int)D_001470C0, 2, 0, (int)&D_001459C0, 0x20, (int)D_00146600, 4, 0, 0, nowait) < 0) {
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
