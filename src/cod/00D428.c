/* asm/cod/00D428.s -> sceLseek64.
 * SCE stdio sceLseek64 over SIF RPC (sceRead template, 00B408). The else-branch "m" fence puts the PRE-inserted
 * hi(D_001470C0)/hi(D_00146600) before mode = 0; that adds a reference to hi(D_001470C0), so an empty asm with
 * "X" operands (no code: the operands stay lo_sum memory references) adds references to hi(D_00132324) and
 * hi(D_001459C0) to restore the image's global-alloc priority order (s4/s5/s6) (Session 45)
 * MATCHED. */
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
    long *ret;                  /* 0x04 */
    int ret_size;               /* 0x08 */
    int iop_fd;                 /* 0x0C */
    long offset;                /* 0x10 */
    int whence;                 /* 0x18 */
    int fd;                     /* 0x1C */
};

extern int D_00132314 __attribute__((section(".data")));
extern int D_00132324 __attribute__((section(".data")));
extern struct Req D_001459C0;
extern struct Fd D_00146EC0[];
extern int D_00146600[];
extern int D_001470C0[];
extern int _sceFs_q[32];
extern char D_00138130[];

struct Fd *func_0010A318(int fd);
int func_0010A798(int a0);
int func_0010A7C8(void);
int func_0010A228(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8, int a9);
int CreateSema(struct SemaParam *param);
int DeleteSema(int sema);
int WaitSema(int sema);
int SignalSema(int sema);

long sceLseek64(int fd, long offset, int whence) {
    struct Req *req = &D_001459C0;
    struct Fd *f;
    struct SemaParam sp;
    long ret[2];
    int mode;
    int nowait;
    int async;
    int sema;
    int st;
    int i;

    f = func_0010A318(fd);
    func_0010A798(0x16);
    if (D_00132314 == 0 || f == 0 || (mode = f->mode) == 0) {
        func_0010A7C8();
        return -9;
    }
    req->iop_fd = f->iop_fd;
    req->offset = offset;
    req->whence = whence;
    req->fd = f - D_00146EC0;
    sp.max_count = 1;
    sp.option = D_00138130;
    sp.init_count = 0;
    async = mode & 0x8000;
    sema = CreateSema(&sp);
    req->ret = ret;
    req->ret_size = 8;
    req->sema = sema;
    if (async) {
        WaitSema(D_00132324);
        i = 0;
        __asm__ __volatile__ ("" : : "m" (_sceFs_q[0]));
        mode = async;
        for (; i < 32; i++) {
            if (_sceFs_q[i] == -1) {
                _sceFs_q[i] = req->sema;
                req->sema = -req->sema;
                break;
            }
        }
        __asm__ __volatile__ ("" : : "X" (D_00132324), "X" (D_001459C0), "X" (D_001459C0));
        SignalSema(D_00132324);
    } else {
        __asm__ __volatile__ ("" : : "m" (D_001470C0[0]), "m" (D_00146600[0]));
        mode = 0;
    }
    if (func_0010A228((int)D_001470C0, 0x16, 0, (int)&D_001459C0, 0x20, (int)D_00146600, 4, 0, 0, mode) < 0) {
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
    if (mode) {
        DeleteSema(sema);
        return 0;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return ret[0];
}
