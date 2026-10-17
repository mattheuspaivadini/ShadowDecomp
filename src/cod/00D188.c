/* asm/cod/00D188.s -> sceMount.
 * SCE libkernel stdio sceMount over SIF RPC (sceClose/sceStdioCCode template)
 * MATCHED. */
struct S00D188Sema {            /* the kernel SemaParam */
    int count;                  /* 0x00 */
    int max_count;              /* 0x04 */
    int init_count;             /* 0x08 */
    int wait_threads;           /* 0x0C */
    int attr;                   /* 0x10 */
    char *option;               /* 0x14 */
};

struct S00D188Req {             /* the send buffer at D_001459C0 */
    int sema;                   /* 0x00 */
    int *ret;                   /* 0x04 */
    int ret_size;               /* 0x08 */
    char name[0x400];           /* 0x0C */
    char newname[0x400];        /* 0x40C */
    char arg[0x400];            /* 0x80C */
    int flag;                   /* 0xC0C */
    int arglen;                 /* 0xC10 */
};

extern int D_00132314 __attribute__((section(".data")));
extern struct S00D188Req D_001459C0;
extern int D_00146600[];
extern int D_001470C0[];
extern char D_00138118[];       /* "SceStdioMountSema" */

int func_0010A798(int a0);
int func_0010A7C8(void);
int func_0010A228(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8, int a9);
int sceFsInit(void);
void sceSifWriteBackDCache(void *addr, int size);
int CreateSema(struct S00D188Sema *param);
int DeleteSema(int sema);
int WaitSema(int sema);

int sceMount(const char *name, const char *newname, int flag, void *arg, int arglen) {
    struct S00D188Req *req = &D_001459C0;
    struct S00D188Sema sp;
    int ret[4];
    int sema;
    int i;
    int st;

    func_0010A798(0x14);
    if (D_00132314 == 0)
        sceFsInit();
    for (i = 0; i < 0x400; i++) {
        if ((req->name[i] = name[i]) == 0)
            break;
    }
    if (i == 0x400)
        req->name[0x3FF] = 0;
    for (i = 0; i < 0x400; i++) {
        if ((req->newname[i] = newname[i]) == 0)
            break;
    }
    if (i == 0x400)
        req->newname[0x3FF] = 0;
    if (arglen > 0x400) {
        func_0010A7C8();
        return -7;
    }
    for (i = 0; i < arglen; i++)
        req->arg[i] = ((char *)arg)[i];
    req->arglen = arglen;
    req->flag = flag;
    sp.max_count = 1;
    sp.option = D_00138118;
    sp.init_count = 0;
    sema = CreateSema(&sp);
    req->ret = ret;
    req->sema = sema;
    req->ret_size = 4;
    sceSifWriteBackDCache(&D_001459C0, 0xC14);
    if (func_0010A228((int)D_001470C0, 0x14, 0, (int)&D_001459C0, 0xC14,
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
