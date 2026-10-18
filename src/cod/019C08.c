/* asm/cod/019C08.s -> sceSifMBindRpcParam.
 * sceSifMBindRpcParam (SceMrpcBind); typed client/record, volatile sema ids (store+reload, kept out of delay slots) (Session 23)
 * MATCHED. */
typedef struct { int count; int max_count; int init_count; int wait_threads; unsigned int attr; void *option; int pad[2]; } ee_sema_t;
struct CD;
struct Rec { char pad00[0x14]; struct Rec *self; int f18; struct CD *cd; int rpc; int size; int a4; int a5; char pad30[0x10]; };
struct CD {
    struct Rec *rec;        /* 0x00 */
    int f04;                /* 0x04 */
    volatile int sema;      /* 0x08 */
    int f0C;                /* 0x0C */
    int rpc;                /* 0x10 */
    char pad14[0x10];
    int server;             /* 0x24 */
    volatile int csema;     /* 0x28 */
    int f2C;                /* 0x2C */
    int size;               /* 0x30 */
    int a4;                 /* 0x34 */
    int a5;                 /* 0x38 */
};
extern char D_00138B28[];
extern char D_00138B50[];
extern char D_00138B60[];
extern char D_001518C0[];
void scePrintf(const char *fmt, ...);
int CreateSema(ee_sema_t *s);
int WaitSema(int s);
int DeleteSema(int s);
struct Rec *func_001199F8(void *pool);
void func_00119AA0(struct Rec *r);
int sceSifSendCmd(int id, void *pkt, int size, void *src, void *dst, int n);

int sceSifMBindRpcParam(struct CD *cd, int rpc, int mode, int size, int a4, int a5) {
    ee_sema_t s;
    struct Rec *r;
    int sema;

    if (mode != 0) {
        scePrintf(D_00138B28);
        return -1;
    }
    s.init_count = 1;
    s.option = D_00138B50;
    s.max_count = 1;
    cd->csema = CreateSema(&s);
    if (cd->csema < 0)
        return -3;
    WaitSema(cd->csema);
    cd->rpc = rpc;
    cd->server = 0;
    cd->size = size;
    cd->a4 = a4;
    cd->a5 = a5;
    r = func_001199F8(D_001518C0);
    if (r == 0) {
        DeleteSema(cd->csema);
        return -1;
    }
    cd->rec = r;
    cd->f04 = r->f18;
    r->rpc = rpc;
    r->size = size;
    r->a4 = a4;
    r->a5 = a5;
    r->self = r;
    r->cd = cd;
    s.max_count = 1;
    s.option = D_00138B60;
    s.init_count = 0;
    cd->sema = CreateSema(&s);
    sema = cd->sema;
    if (sema < 0) {
        func_00119AA0(r);
        DeleteSema(cd->csema);
        return -3;
    }
    if (sceSifSendCmd(0x80000019, r, 0x40, 0, 0, 0) == 0) {
        func_00119AA0(r);
        DeleteSema(sema);
        DeleteSema(cd->csema);
        return -2;
    }
    WaitSema(sema);
    DeleteSema(sema);
    if (cd->server == 0)
        DeleteSema(cd->csema);
    return 0;
}
