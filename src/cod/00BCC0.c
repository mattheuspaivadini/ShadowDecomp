/* asm/cod/00BCC0.s -> sceIoctl2.
 * SCE libkernel stdio sceIoctl2 over SIF RPC (sceClose/sceStdioCCode template)
 * MATCHED. */
struct S00BCC0Fd {              /* 16-byte EE fd records at D_00146EC0 */
    int iop_fd;                 /* 0x00 */
    int used;                   /* 0x04 */
    int f08;
    int f0C;
};

struct S00BCC0Sema {            /* the kernel SemaParam */
    int count;                  /* 0x00 */
    int max_count;              /* 0x04 */
    int init_count;             /* 0x08 */
    int wait_threads;           /* 0x0C */
    int attr;                   /* 0x10 */
    char *option;               /* 0x14 */
};

struct S00BCC0Req {             /* the send buffer at D_001459C0 */
    int sema;                   /* 0x00 */
    int *ret;                   /* 0x04 */
    int ret_size;               /* 0x08 */
    int iop_fd;                 /* 0x0C */
    int cmd;                    /* 0x10 */
    char arg[0x400];            /* 0x14 */
    void *buf;                  /* 0x414 */
    unsigned int buflen;        /* 0x418 */
    unsigned int arglen;        /* 0x41C */
};

extern int D_00132314 __attribute__((section(".data")));
extern struct S00BCC0Req D_001459C0;
extern int D_00146600[];
extern int D_001470C0[];
extern char D_00138010[];       /* "SceStdioIoctl2Sema" */

struct S00BCC0Fd *func_0010A318(int fd);
int func_0010A798(int a0);
int func_0010A7C8(void);
int func_0010A228(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8, int a9);
int sceFsInit(void);
void sceSifWriteBackDCache(void *addr, int size);
void *func_0012821C(void *, const void *, unsigned int);   /* memcpy */
int CreateSema(struct S00BCC0Sema *param);
int DeleteSema(int sema);
int WaitSema(int sema);

int sceIoctl2(int fd, int cmd, void *arg, unsigned int arglen, void *buf,
              unsigned int buflen) {
    struct S00BCC0Req *req = &D_001459C0;
    struct S00BCC0Fd *f;
    struct S00BCC0Sema sp;
    int ret[4];
    int sema;
    int st;

    f = func_0010A318(fd);
    func_0010A798(0x1A);
    if (D_00132314 == 0)
        sceFsInit();
    if (f == 0 || f->used == 0) {
        func_0010A7C8();
        return -9;
    }
    if (arglen > 0x400 || buflen > 0x400) {
        func_0010A7C8();
        return -0x16;
    }
    if (arg == 0)
        req->arglen = 0;
    else
        func_0012821C(req->arg, arg, arglen);
    req->iop_fd = f->iop_fd;
    req->cmd = cmd;
    req->arglen = arglen;
    sp.max_count = 1;
    sp.option = D_00138010;
    sp.init_count = 0;
    sema = CreateSema(&sp);
    req->buflen = buflen;
    req->ret = ret;
    req->ret_size = 4;
    req->buf = buf;
    req->sema = sema;
    sceSifWriteBackDCache(&D_001459C0, 0x420);
    if (func_0010A228((int)D_001470C0, 0x1A, 0, (int)&D_001459C0, 0x420,
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
