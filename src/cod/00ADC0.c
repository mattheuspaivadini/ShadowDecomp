/* asm/cod/00ADC0.s -> sceOpen.
 * SCE libkernel stdio sceOpen over SIF RPC; req pinned to s1, st reused as the fd return, iop_fd stored before the mode update (Session 36)
 * MATCHED. */
#include "stdarg.h"

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

struct OpenReq {                /* the send buffer at D_001459C0 */
    int sema;                   /* 0x000 */
    int *ret;                   /* 0x004 */
    int ret_size;               /* 0x008 */
    int flags;                  /* 0x00C */
    int mode;                   /* 0x010 */
    char name[0x400];           /* 0x014 */
    int fd;                     /* 0x414 */
};

extern int D_00132314 __attribute__((section(".data")));
extern int D_00132320 __attribute__((section(".data")));
extern struct OpenReq D_001459C0;
extern struct Fd D_00146EC0[];
extern int D_00146600[];
extern int D_001470C0[];
extern char D_00137F80[];

int func_0010A798(int a0);
int func_0010A7C8(void);
int sceFsInit(void);
int func_0010AAC8(void);
struct Fd *func_0010A1A0(void);
int func_0010A228(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8, int a9);
int CreateSema(struct SemaParam *param);
int DeleteSema(int sema);
int WaitSema(int sema);
int SignalSema(int sema);

int sceOpen(const char *name, int flags, ...) {
    register struct OpenReq *req asm("$17") = &D_001459C0;
    struct Fd *f;
    struct SemaParam sp;
    int ret[4];
    va_list ap;
    int mode;
    int sema;
    int st;
    int fd;
    int i;

    func_0010A798(0);
    if (D_00132314 == 0)
        sceFsInit();
    if (func_0010AAC8() != 0) {
        func_0010A7C8();
        return 0xFFFEFFFC;
    }
    f = func_0010A1A0();
    if (f == 0) {
        func_0010A7C8();
        return -0x13;
    }
    va_start(ap, flags);
    mode = va_arg(ap, int);
    va_end(ap);
    for (i = 0; i < 0x400; i++) {
        if ((req->name[i] = name[i]) == 0)
            break;
    }
    if (i == 0x400)
        req->name[0x3FF] = 0;
    fd = f - D_00146EC0;
    req->flags = flags & 0x7FFFFFFF;
    req->mode = mode;
    req->fd = fd;
    sp.max_count = 1;
    sp.option = D_00137F80;
    sp.init_count = 0;
    sema = CreateSema(&sp);
    req->ret = ret;
    req->sema = sema;
    req->ret_size = 4;
    if (func_0010A228((int)D_001470C0, 0, 0, (int)&D_001459C0, 0x418, (int)D_00146600, 4, 0, 0, 0) < 0) {
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
    if (ret[0] < 0) {
        WaitSema(D_00132320);
        f->mode = 0;
        SignalSema(D_00132320);
        return ret[0];
    }
    st = fd;
    WaitSema(D_00132320);
    f->iop_fd = ret[0];
    f->mode |= flags;
    SignalSema(D_00132320);
    return st;
}
