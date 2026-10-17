/* asm/cod/00D910.s -> sceSymlink.
 * SCE libkernel stdio sceSymlink over SIF RPC (sceClose/sceStdioCCode template)
 * MATCHED. */
struct S00D910Sema {            /* the kernel SemaParam */
    int count;                  /* 0x00 */
    int max_count;              /* 0x04 */
    int init_count;             /* 0x08 */
    int wait_threads;           /* 0x0C */
    int attr;                   /* 0x10 */
    char *option;               /* 0x14 */
};

struct S00D910Req {             /* the send buffer at D_001459C0 */
    int sema;                   /* 0x00 */
    int *ret;                   /* 0x04 */
    int ret_size;               /* 0x08 */
    char name[0x400];           /* 0x0C */
    char newname[0x400];        /* 0x40C */
};

extern int D_00132314 __attribute__((section(".data")));
extern struct S00D910Req D_001459C0;
extern int D_00146600[];
extern int D_001470C0[];
extern char D_00138160[];       /* "SceStdioSymlinkSema" */

int func_0010A798(int a0);
int func_0010A7C8(void);
int func_0010A228(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8, int a9);
int sceFsInit(void);
int CreateSema(struct S00D910Sema *param);
int DeleteSema(int sema);
int WaitSema(int sema);

int sceSymlink(const char *name, const char *newname) {
    struct S00D910Req *req = &D_001459C0;
    struct S00D910Sema sp;
    int ret[4];
    int sema;
    int i;
    int st;

    func_0010A798(0x11);
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
    sp.max_count = 1;
    sp.option = D_00138160;
    sp.init_count = 0;
    sema = CreateSema(&sp);
    req->ret = ret;
    req->sema = sema;
    req->ret_size = 4;
    if (func_0010A228((int)D_001470C0, 0x18, 0, (int)&D_001459C0, 0x80C,
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
