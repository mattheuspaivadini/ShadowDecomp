/* asm/cod/00CB60.s -> sceChstat.
 * SCE libkernel stdio sceChstat over SIF RPC (sceClose/sceStdioCCode template)
 * MATCHED. */
struct S00CB60Sema {            /* the kernel SemaParam */
    int count;                  /* 0x00 */
    int max_count;              /* 0x04 */
    int init_count;             /* 0x08 */
    int wait_threads;           /* 0x0C */
    int attr;                   /* 0x10 */
    char *option;               /* 0x14 */
};

struct S00CB60Stat {            /* the 0x40-byte sce_stat */
    unsigned int mode;          /* 0x00 */
    unsigned int attr;          /* 0x04 */
    unsigned int size;          /* 0x08 */
    unsigned char ctime[8];     /* 0x0C */
    unsigned char atime[8];     /* 0x14 */
    unsigned char mtime[8];     /* 0x1C */
    unsigned int hisize;        /* 0x24 */
    unsigned int private_[6];   /* 0x28 */
};

struct S00CB60Req {             /* the send buffer at D_001459C0 */
    int sema;                   /* 0x00 */
    int *ret;                   /* 0x04 */
    int ret_size;               /* 0x08 */
    unsigned int mask;          /* 0x0C */
    struct S00CB60Stat stat;    /* 0x10 */
    unsigned char name[0x400];  /* 0x50 */
};

extern int D_00132314 __attribute__((section(".data")));
extern struct S00CB60Req D_001459C0;
extern int D_00146600[];
extern int D_001470C0[];
extern char D_001380D0[];       /* "SceStdioChstatSema" */

int func_0010A798(int a0);
int func_0010A7C8(void);
int func_0010A228(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8, int a9);
int sceFsInit(void);
void sceSifWriteBackDCache(void *addr, int size);
int CreateSema(struct S00CB60Sema *param);
int DeleteSema(int sema);
int WaitSema(int sema);

int sceChstat(const char *name, struct S00CB60Stat *stat, unsigned int mask) {
    struct S00CB60Req *req = &D_001459C0;
    struct S00CB60Sema sp;
    int ret[4];
    int sema;
    int i;
    int st;

    func_0010A798(0xD);
    if (D_00132314 == 0)
        sceFsInit();
    for (i = 0; i < 0x400; i++) {
        if ((req->name[i] = name[i]) == 0)
            break;
    }
    if (i == 0x400) {
        req->name[0x3FF] = 0;
        i = 0x3FF;
    }
    req->stat = *stat;
    req->mask = mask;
    sp.max_count = 1;
    sp.option = D_001380D0;
    sp.init_count = 0;
    sema = CreateSema(&sp);
    req->ret = ret;
    req->sema = sema;
    req->ret_size = 4;
    sceSifWriteBackDCache(&D_001459C0, 0x450);
    if (func_0010A228((int)D_001470C0, 0xD, 0, (int)&D_001459C0, i + 0x51,
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
