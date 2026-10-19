/* STATUS (Session 34, 2026-10-19): NON_MATCHING. best score 56 [cc=29].
 * sceSifMCallRpc (libmrpc). Residual = the two alignment printfs share one call, the $gp copy goes
 * through a temporary, has_end test order and sema store/test.
 * Tried: goto-shared printf, asm move from $gp, if/else swap, separate sema store; the asm $gp copy
 * shifts scheduling (620 vs 624 bytes).
 * The original .s stays in the build (asm/cod/019F18.s); this C
 * draft (Session 34) is kept for the record. */
typedef struct { int count; int max_count; int init_count; int wait_threads; unsigned int attr; void *option; int pad[2]; } ee_sema_t;
struct CD;
struct Rec {
    char pad00[0x14];
    struct Rec *self;           /* 0x14 */
    int f18;                    /* 0x18 */
    struct CD *cd;              /* 0x1C */
    int rpc;                    /* 0x20 */
    int ssize;                  /* 0x24 */
    void *recv;                 /* 0x28 */
    int rsize;                  /* 0x2C */
    int has_end;                /* 0x30 */
    int server;                 /* 0x34 */
    char pad38[8];
};
struct CD {
    struct Rec *rec;            /* 0x00 */
    int f04;                    /* 0x04 */
    volatile int sema;          /* 0x08 */
    int f0C;                    /* 0x0C */
    int rpc;                    /* 0x10 */
    void *dest;                 /* 0x14 */
    void *gp;                   /* 0x18 */
    void (*end_func)(void *);   /* 0x1C */
    void *end_param;            /* 0x20 */
    int server;                 /* 0x24 */
    volatile int csema;         /* 0x28 */
};

register void *gp_reg asm ("$28");

extern char D_00138B28[];
extern char D_00138B80[];
extern char D_00138BB8[];
extern char D_00138BC8[];
extern char D_00138C00[];
extern char D_001518C0[];
void scePrintf(const char *fmt, ...);
int CreateSema(ee_sema_t *s);
int WaitSema(int s);
int DeleteSema(int s);
struct Rec *func_001199F8(void *pool);
void func_00119AA0(struct Rec *r);
void sceSifWriteBackDCache(void *p, int size);
int sceSifSendCmd(int id, void *pkt, int size, void *src, void *dst, int n);

int sceSifMCallRpc(struct CD *cd, int rpc, int mode, void *send, int ssize, void *recv, int rsize,
                   void (*end_func)(void *), void *end_param) {
    ee_sema_t s;
    struct Rec *r;
    int sema;

    if (mode != 0) {
        scePrintf(D_00138B28);
        return -1;
    }
    WaitSema(cd->csema);
    if ((unsigned int)send & 0x3F) {
        scePrintf(D_00138B80, D_00138BB8, send);
        return -1;
    }
    if ((unsigned int)recv & 0x3F) {
        scePrintf(D_00138BC8, D_00138BB8, recv);
        return -1;
    }
    r = func_001199F8(D_001518C0);
    if (r == 0)
        return -1;
    cd->end_param = end_param;
    cd->f04 = r->f18;
    cd->rec = r;
    cd->end_func = end_func;
    cd->gp = gp_reg;
    r->rpc = rpc;
    r->self = r;
    r->ssize = ssize;
    r->recv = recv;
    r->rsize = rsize;
    r->cd = cd;
    r->server = cd->server;
    if (send == recv) {
        sceSifWriteBackDCache(send, ssize < rsize ? rsize : ssize);
    } else {
        if (ssize > 0)
            sceSifWriteBackDCache(send, ssize);
        if (rsize > 0)
            sceSifWriteBackDCache(recv, rsize);
    }
    if (mode & 1) {
        if (end_func != 0)
            r->has_end = 1;
        else
            r->has_end = 0;
        cd->sema = -1;
        if (sceSifSendCmd(0x8000001A, r, 0x40, send, cd->dest, ssize) != 0)
            return 0;
        func_00119AA0(r);
        return -2;
    }
    s.init_count = 0;
    s.option = D_00138C00;
    s.max_count = 1;
    cd->sema = sema = CreateSema(&s);
    if (sema < 0) {
        func_00119AA0(r);
        return -3;
    }
    r->has_end = 1;
    if (sceSifSendCmd(0x8000001A, r, 0x40, send, cd->dest, ssize) == 0) {
        func_00119AA0(r);
        DeleteSema(sema);
        return -2;
    }
    WaitSema(sema);
    DeleteSema(sema);
    return 0;
}
