/* STATUS (Session 41, 2026-10-21): NON_MATCHING. best score 6 (was 8; sw.py diff lines).
 * A pointer local h = D_00147140 assigned before sceSifInitRpc keeps %hi in s0 and the full address in s1 (10 -> 6 instructions). Residual: prologue sched2 tie (image saves s0 first, then lui s0; ours sd s1 first). Tried store order, h types, struct H, pin on oldi, asm uses of h, 13 single flags.
 * sceFsInit. Non-gp globals via section attributes, oldi pinned to s0, first handler-data store before
 * sceSifInitRpc. Residual = %hi(D_00147140) should stay in s0 while s1 gets the full address.
 * Tried: pointer local, pinned pointer local, struct-typed D_00147140, D_00132314/D_00132318 store
 * order.
 * The original .s stays in the build (asm/cod/00A8C0.s); this C
 * draft (Session 34) is kept for the record. */
struct Iob { int f0; int f4; int f8; int fC; };
struct FioCd { char pad00[0x24]; int server; char pad28[0x18]; };
struct FioBuf { void *a; void *b; };

extern struct FioCd D_001470C0;
extern int D_00147100[];
extern int D_00147140[];
extern struct Iob D_00146EC0[0x20];
extern int D_00132320 __attribute__((section(".data")));
extern struct FioBuf D_00145980 __attribute__((section(".data")));
extern char D_00146640[];
extern char D_00146600[];
extern int D_001470E8 __attribute__((section(".bss")));
extern int D_00132314 __attribute__((section(".data")));
extern int D_00132318 __attribute__((section(".data")));

void sceSifInitRpc(int mode);
int DIntr(void);
int EIntr(void);
void sceSifAddCmdHandler(int cmd, void (*fn)(void *, void *), void *data);
int sceSifBindRpc(struct FioCd *cd, int rpc, int mode);
void func_0010A388(void *, void *);
void func_0010A878(void *, void *);
void func_0010A0B0(void);
int WaitSema(int s);
int SignalSema(int s);
int func_0010A228(struct FioCd *cd, int fno, int mode, void *send, int ssize, void *recv, int rsize,
                  void *end, void *param, int a9);

int sceFsInit(void) {
    int oldi;
    int i;
    struct Iob *p;
    int mode;
    int *h;

    h = D_00147140;
    sceSifInitRpc(0);
    h[0] = 0;
    h[1] = 0;
    oldi = DIntr();
    sceSifAddCmdHandler(0x80000011, func_0010A388, D_00147100);
    sceSifAddCmdHandler(0x80000013, func_0010A878, h);
    if (oldi) EIntr();
    for (;;) {
        if (sceSifBindRpc(&D_001470C0, 0x80000001, 0) < 0) return -22;
        if (D_001470C0.server != 0) break;
        i = 0x100000;
        while (i--)
            ;
    }
    func_0010A0B0();
    WaitSema(D_00132320);
    for (p = D_00146EC0; p < D_00146EC0 + 0x20; p++)
        p->f4 = 0;
    SignalSema(D_00132320);
    D_00145980.a = D_00146640;
    D_00145980.b = D_00146640 + 0x440;
    if (func_0010A228(&D_001470C0, 0xFF, 0, &D_00145980, 8, D_00146600, 8, 0, 0, 0) < 0)
        return 0xFFFEFFFF;
    __builtin_memcpy(&D_001470E8, (char *)((unsigned int)D_00146600 | 0x20000000), 4);
    __builtin_memcpy(&mode, (char *)((unsigned int)(D_00146600 + 4) | 0x20000000), 4);
    D_00132318 = mode == 2;
    D_00132314 = 1;
    return 0;
}
