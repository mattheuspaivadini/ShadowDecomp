/* STATUS (Session 43, 2026-10-21): NON_MATCHING. best score 3 (was 3; sw.py diff lines).
 * PRE lever (Session 43): the else-branch luis are gcse PRE insertions appended after mode = 0 (t.c.gcse: PRE/HOIST edge (11,12) expressions 28/31, numbered by first occurrence, so a B-only fence flips the insertion order). An else fence asm volatile with "m"(D_001470C0[0]), "m"(D_00146600[0]) before mode = 0 gives the exact schedule but a pure s5/s6 rename: the fence adds a ref to the hi(D_001470C0) pseudo (6 refs/232 insns beats hi(D_00132324) 3/66 in greg). Tried: 228 fence position/order combos (build/s43/pre_grid.py), mode/async/sema pins, no-else and join forms (39+), "m"(D_00132324) uses to raise its priority (27+), 1008-variant fence grid on top (13).
 * sceLseek: same template as the matched sceRead (00B408). Levers: a volatile asm with an "m"(_sceFs_q[0])
 * operand after i = 0 forces the hi() of the queue address before i = 0 and keeps the nowait copy after
 * it (the copy lands in the bne slot, as in the image). Residual = the else-branch `move s2,zero`,
 * which the image schedules after the two hi() luis. An asm "m" fence on D_001470C0/D_00146600 in the
 * else branch fixes the order but swaps s5/s6 (hi(D_00132324) is allocated last); extra references
 * to D_00132324, pins on sema, a join-side fence and swapped if/else layout all fail.
 * The original .s stays in the build (asm/cod/00B1C8.s); this C
 * draft (Session 40) is kept for the record. */
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
    int offset;                 /* 0x10 */
    int whence;                 /* 0x14 */
    int fd;                     /* 0x18 */
};

extern int D_00132314 __attribute__((section(".data")));
extern int D_00132324 __attribute__((section(".data")));
extern struct Req D_001459C0;
extern struct Fd D_00146EC0[];
extern int D_00146600[];
extern int D_001470C0[];
extern int _sceFs_q[32];
extern char D_00137FB0[];

struct Fd *func_0010A318(int fd);
int func_0010A798(int a0);
int func_0010A7C8(void);
int func_0010A228(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8, int a9);
int CreateSema(struct SemaParam *param);
int DeleteSema(int sema);
int WaitSema(int sema);
int SignalSema(int sema);

int sceLseek(int fd, int offset, int whence) {
    struct Req *req = &D_001459C0;
    struct Fd *f;
    struct SemaParam sp;
    int ret[4];
    int mode;
    int nowait;
    int async;
    int sema;
    int st;
    int i;

    f = func_0010A318(fd);
    func_0010A798(4);
    if (D_00132314 == 0 || f == 0 || (mode = f->mode) == 0) {
        func_0010A7C8();
        return -9;
    }
    req->iop_fd = f->iop_fd;
    req->offset = offset;
    req->whence = whence;
    req->fd = f - D_00146EC0;
    sp.max_count = 1;
    sp.option = D_00137FB0;
    sp.init_count = 0;
    async = mode & 0x8000;
    sema = CreateSema(&sp);
    req->ret = ret;
    req->ret_size = 4;
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
        SignalSema(D_00132324);
    } else {
        mode = 0;
    }
    if (func_0010A228((int)D_001470C0, 4, 0, (int)&D_001459C0, 0x1C, (int)D_00146600, 4, 0, 0, mode) < 0) {
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
