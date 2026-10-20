/* STATUS (Session 36, 2026-10-20): NON_MATCHING. best score 26 [cc=29].
 * sceIoctl: request 1 = any async request pending (scan _sceFs_q), 2/3 = 32/64-bit read of the
 * uncached status slot D_00146650[D_00132310], else a 0x400-byte argument block over RPC 5. Needs
 * D_00145988 in .bss. Residuals: the original keeps the case-1 constant in s5 (li s5,1 in the
 * prologue) and has the same i = 0 delay-slot difference as sceLseek. Tried: switch vs if-chain
 * orders, loop forms, i types, cc sweep.
 * The original .s stays in the build (asm/cod/00B938.s); this C
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

struct IoctlData {
    char b[0x400];
};

struct IoctlReq {               /* the send buffer at D_001459C0 */
    int sema;                   /* 0x000 */
    int *ret;                   /* 0x004 */
    int ret_size;               /* 0x008 */
    int iop_fd;                 /* 0x00C */
    int req;                    /* 0x010 */
    struct IoctlData data;      /* 0x014 */
    int f414;                   /* 0x414 */
    int f418;                   /* 0x418 */
    int datalen;                /* 0x41C */
};

extern int D_00132310 __attribute__((section(".data")));
extern int D_00132314 __attribute__((section(".data")));
extern int D_00132324 __attribute__((section(".data")));
extern void *D_00145988 __attribute__((section(".bss")));
extern struct IoctlReq D_001459C0;
extern int D_00146600[];
extern char D_00146650[];
extern int D_001470C0[];
extern int _sceFs_q[32];
extern char D_00137FF8[];

struct Fd *func_0010A318(int fd);
int func_0010A798(int a0);
int func_0010A7C8(void);
int sceFsInit(void);
int func_0010A228(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8, int a9);
void sceSifWriteBackDCache(void *addr, int size);
int CreateSema(struct SemaParam *param);
int DeleteSema(int sema);
int WaitSema(int sema);
int SignalSema(int sema);

int sceIoctl(int fd, int req, void *arg) {
    struct IoctlReq *r = &D_001459C0;
    struct Fd *f;
    struct SemaParam sp;
    int ret[4];
    int sema;
    int st;
    int i;

    f = func_0010A318(fd);
    func_0010A798(5);
    D_00145988 = arg;
    if (D_00132314 == 0)
        sceFsInit();
    if (f == 0 || f->mode == 0) {
        func_0010A7C8();
        return -9;
    }
    r->f414 = 0;
    r->f418 = 0;
    switch (req) {
    case 1:
        WaitSema(D_00132324);
        for (i = 0; i < 32; i++) {
            if (_sceFs_q[i] != -1)
                break;
        }
        if (i == 32)
            *(int *)D_00145988 = 0;
        else
            *(int *)D_00145988 = 1;
        SignalSema(D_00132324);
        func_0010A7C8();
        return 0;
    case 2:
        *(int *)arg = *(int *)((unsigned int)(D_00146650 + D_00132310 * 0x440) | 0x20000000);
        func_0010A7C8();
        return 0;
    case 3:
        *(long *)arg = *(long *)((unsigned int)(D_00146650 + D_00132310 * 0x440) | 0x20000000);
        func_0010A7C8();
        return 0;
    }
    r->iop_fd = f->iop_fd;
    r->req = req;
    if (arg == 0) {
        r->datalen = 0;
    } else {
        r->datalen = 0x400;
        r->data = *(struct IoctlData *)arg;
    }
    sp.max_count = 1;
    sp.option = D_00137FF8;
    sp.init_count = 0;
    sema = CreateSema(&sp);
    r->ret = ret;
    r->ret_size = 4;
    r->sema = sema;
    sceSifWriteBackDCache(&D_001459C0, 0x420);
    if (func_0010A228((int)D_001470C0, 5, 0, (int)&D_001459C0, 0x420,
                      (int)D_00146600, 4, 0, 0, 0) < 0) {
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
    WaitSema(sema);
    DeleteSema(sema);
    return ret[0];
}
