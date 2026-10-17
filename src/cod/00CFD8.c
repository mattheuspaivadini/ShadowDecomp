/* asm/cod/00CFD8.s -> sceSync.
 * SCE libkernel stdio sceSync over SIF RPC (sceClose/sceStdioCCode template)
 * MATCHED. */
struct S00CFD8Sema {            /* the kernel SemaParam */
    int count;                  /* 0x00 */
    int max_count;              /* 0x04 */
    int init_count;             /* 0x08 */
    int wait_threads;           /* 0x0C */
    int attr;                   /* 0x10 */
    char *option;               /* 0x14 */
};

struct S00CFD8Req {             /* the send buffer at D_001459C0 */
    int sema;                   /* 0x00 */
    int *ret;                   /* 0x04 */
    int ret_size;               /* 0x08 */
    int f0C;                    /* 0x0C */
    int flag;                   /* 0x10 */
    char name[0x400];           /* 0x14 */
};

extern int D_00132314 __attribute__((section(".data")));
extern struct S00CFD8Req D_001459C0;
extern int D_00146600[];
extern int D_001470C0[];
extern char D_00138100[];       /* "SceStdioSyncSema" */

int func_0010A798(int a0);
int func_0010A7C8(void);
int func_0010A228(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8, int a9);
int sceFsInit(void);
int CreateSema(struct S00CFD8Sema *param);
int DeleteSema(int sema);
int WaitSema(int sema);

int sceSync(const char *name, int flag) {
    struct S00CFD8Req *req = &D_001459C0;
    struct S00CFD8Sema sp;
    int ret[4];
    int sema;
    int i;
    int st;

    func_0010A798(0x13);
    if (D_00132314 == 0)
        sceFsInit();
    for (i = 0; i < 0x400; i++) {
        if ((req->name[i] = name[i]) == 0)
            break;
    }
    if (i == 0x400)
        req->name[0x3FF] = 0;
    req->flag = flag;
    sp.max_count = 1;
    sp.option = D_00138100;
    sp.init_count = 0;
    sema = CreateSema(&sp);
    req->ret = ret;
    req->sema = sema;
    req->ret_size = 4;
    if (func_0010A228((int)D_001470C0, 0x13, 0, (int)&D_001459C0, 0x414,
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
