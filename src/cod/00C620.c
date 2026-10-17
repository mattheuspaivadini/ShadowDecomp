/* asm/cod/00C620.s -> sceDopen.
 * SCE libkernel stdio sceDopen over SIF RPC (sceClose/sceStdioCCode template)
 * MATCHED. */
struct S00C620Fd {              /* 16-byte EE fd records at D_00146EC0 */
    int iop_fd;                 /* 0x00 */
    int used;                   /* 0x04 */
    int f08;
    int f0C;
};

extern int D_00132314 __attribute__((section(".data")));
extern int D_00132320 __attribute__((section(".data")));   /* fd-table sema */
extern struct S00C620Fd D_00146EC0[];

int func_0010A798(int a0);
int func_0010A7C8(void);
struct S00C620Fd *func_0010A1A0(void);
int sceFsInit(void);
int sceStdioCCode(const char *name, int cmd);
int WaitSema(int sema);
int SignalSema(int sema);

int sceDopen(const char *name) {
    struct S00C620Fd *f;
    int r;

    func_0010A798(9);
    if (D_00132314 == 0)
        sceFsInit();
    func_0010A7C8();
    f = func_0010A1A0();
    if (f == 0)
        return -0x13;
    r = sceStdioCCode(name, 9);
    if (r < 0) {
        WaitSema(D_00132320);
        f->used = 0;
        SignalSema(D_00132320);
        return r;
    }
    WaitSema(D_00132320);
    f->iop_fd = r;
    r = f - D_00146EC0;
    SignalSema(D_00132320);
    return r;
}
