/* asm/cod/00C4D0.s -> sceAddDrv.
 * SCE libkernel stdio sceAddDrv over SIF RPC (sceClose/sceStdioCCode template)
 * MATCHED. */
struct S00C4D0Sema {            /* the kernel SemaParam */
    int count;                  /* 0x00 */
    int max_count;              /* 0x04 */
    int init_count;             /* 0x08 */
    int wait_threads;           /* 0x0C */
    int attr;                   /* 0x10 */
    char *option;               /* 0x14 */
};

extern int D_00132314 __attribute__((section(".data")));
extern int D_001459C0[];
extern int D_00146600[];
extern int D_001470C0[];
extern char D_00138070[];       /* "SceStdioAddDrvSema" */

int func_0010A798(int a0);
int sceFsInit(void);
int func_0010A7C8(void);
int func_0010A228(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8, int a9);
int CreateSema(struct S00C4D0Sema *param);
int DeleteSema(int sema);
int WaitSema(int sema);

int sceAddDrv(void *drv) {
    int *args = D_001459C0;
    struct S00C4D0Sema sp;
    int ret[4];
    int sema;
    int st;

    func_0010A798(0xF);
    if (D_00132314 == 0)
        sceFsInit();
    args[3] = (int)drv;
    sp.max_count = 1;
    sp.option = D_00138070;
    sp.init_count = 0;
    sema = CreateSema(&sp);
    args[0] = sema;
    args[1] = (int)ret;
    args[2] = 4;
    if (func_0010A228((int)D_001470C0, 0xF, 0, (int)args, 0x10,
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
