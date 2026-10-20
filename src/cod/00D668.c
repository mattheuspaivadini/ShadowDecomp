/* asm/cod/00D668.s -> sceDevctl.
 * SCE libkernel stdio sceDevctl over SIF RPC; one ret word (bufp spill sits above it), command 0x4601 block write-back, store order from a grid (Session 36)
 * MATCHED. */
struct SemaParam {
    int count;                  /* 0x00 */
    int max_count;              /* 0x04 */
    int init_count;             /* 0x08 */
    int wait_threads;           /* 0x0C */
    int attr;                   /* 0x10 */
    char *option;               /* 0x14 */
};

struct DevctlReq {              /* the send buffer at D_001459C0 */
    int sema;                   /* 0x000 */
    int *ret;                   /* 0x004 */
    int ret_size;               /* 0x008 */
    char name[0x400];           /* 0x00C */
    char arg[0x400];            /* 0x40C */
    int cmd;                    /* 0x80C */
    unsigned int arglen;        /* 0x810 */
    void *bufp;                 /* 0x814 */
    unsigned int buflen;        /* 0x818 */
};

struct DevctlBlock {            /* the argument of devctl command 0x4601 */
    int f00;
    int count;                  /* 0x04 */
    void *buf;                  /* 0x08 */
    int size;                   /* 0x0C */
};

extern int D_00132314 __attribute__((section(".data")));
extern struct DevctlReq D_001459C0;
extern int D_00146600[];
extern int D_001470C0[];
extern char D_00138148[];

int func_0010A798(int a0);
int func_0010A7C8(void);
int func_0010A228(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8, int a9);
int sceFsInit(void);
void sceSifWriteBackDCache(void *addr, int size);
int CreateSema(struct SemaParam *param);
int DeleteSema(int sema);
int WaitSema(int sema);

int sceDevctl(const char *name, int cmd, void *arg, unsigned int arglen, void *bufp, unsigned int buflen) {
    struct DevctlReq *req = &D_001459C0;
    struct SemaParam sp;
    int ret;
    int sema;
    int st;
    int rpc;
    int i;

    func_0010A798(0x17);
    if (D_00132314 == 0)
        sceFsInit();
    for (i = 0; i < 0x400; i++) {
        if ((req->name[i] = name[i]) == 0)
            break;
    }
    if (i == 0x400)
        req->name[0x3FF] = 0;
    if (arglen > 0x400 || buflen > 0x400)
        goto inval;
    if (cmd == 0x4601) {
        if (((struct DevctlBlock *)arg)->count == 0) {
            func_0010A7C8();
            return 0;
        }
        if (((struct DevctlBlock *)arg)->size == 0) {
        inval:
            func_0010A7C8();
            return -0x16;
        }
    }
    for (i = 0; i < arglen; i++)
        req->arg[i] = ((char *)arg)[i];
    req->arglen = arglen;
    sp.max_count = 1;
    sp.option = D_00138148;
    req->cmd = cmd;
    sp.init_count = 0;
    sema = CreateSema(&sp);
    req->buflen = buflen;
    req->ret = &ret;
    req->ret_size = 4;
    req->bufp = bufp;
    req->sema = sema;
    if (cmd == 0x4601) {
        rpc = 0x1C;
        sceSifWriteBackDCache(((struct DevctlBlock *)arg)->buf,
                              ((struct DevctlBlock *)arg)->count * ((struct DevctlBlock *)arg)->size);
    } else {
        rpc = 0x17;
    }
    sceSifWriteBackDCache(&D_001459C0, 0x81C);
    if (func_0010A228((int)D_001470C0, rpc, 0, (int)&D_001459C0, 0x81C,
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
    return ret;
}
