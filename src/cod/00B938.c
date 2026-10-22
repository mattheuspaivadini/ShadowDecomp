/* asm/cod/00B938.s -> sceIoctl.
 * SCE stdio sceIoctl over SIF RPC (request 1 = queue busy, 2/3 = 32/64-bit status read, else RPC 5).
 * The case-1 constant lives in s5 from the prologue: a local initialised to 1 that CSE reuses in the
 * compare, so the dispatch is written as the switch's compare tree (2, <3, 1, 3) with that local. An
 * empty asm taking the first queue word, -1 and i (no code) stops reorg from pulling i = 0 into the
 * bne slot, as in the image; r->ret, r->sema, r->ret_size store order (Session 45)
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
    int m, x;
    int one = 1;

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
    if (req == 2) goto c2;
    if (req < 3) {
        if (req == one) goto c1;
        goto dflt;
    }
    if (req == 3) goto c3;
    goto dflt;
c1:
    WaitSema(D_00132324);
    i = 0;
    x = _sceFs_q[0];
    m = -1;
    asm("" : "+r"(x), "+r"(m) : "r"(i));
    if (x == m) {
        do
            i++;
        while (i < 32 && _sceFs_q[i] == -1);
    }
    if (i == 32)
        *(int *)D_00145988 = 0;
    else
        *(int *)D_00145988 = 1;
    SignalSema(D_00132324);
    func_0010A7C8();
    return 0;
c2:
    *(int *)arg = *(int *)((unsigned int)(D_00146650 + D_00132310 * 0x440) | 0x20000000);
    func_0010A7C8();
    return 0;
c3:
    *(long *)arg = *(long *)((unsigned int)(D_00146650 + D_00132310 * 0x440) | 0x20000000);
    func_0010A7C8();
    return 0;
dflt:
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
    r->sema = sema;
    r->ret_size = 4;
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
