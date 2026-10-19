/* STATUS (Session 34, 2026-10-19): NON_MATCHING. best score 58 [cc=29].
 * sceMc2Init (3 semas + server thread). Frame fixed with an extra 0x30 local after the ThreadParam.
 * Residual = s-register roles (constant 1 in s2, &D_00151E20 in s5/s6) and the order of the -1 handle
 * stores.
 * Tried: declaration order, pad array vs second ThreadParam.
 * The original .s stays in the build (asm/cod/01A188.s); this C
 * draft (Session 34) is kept for the record. */
struct SemaParam {
    int currentCount;
    int maxCount;
    int initCount;
    int numWaitThreads;
    unsigned int attr;
    unsigned int option;
};

struct ThreadParam {
    int status;
    void *func;
    void *stack;
    int stackSize;
    void *gpReg;
    int initPriority;
    int currentPriority;
    unsigned int attr;
    unsigned int option;
    int waitType;
    int waitId;
    int wakeupCount;
};

struct H { int thid; int sema0; int sema1; };
extern int D_00135630[];
extern int D_00151904[];
extern struct H D_00151E20;
extern int D_00151E2C[];
extern char D_00151E40[];
extern char D_00138C10[];
extern char D_00138C28[];
extern char D_00138C40[];
extern char D_00138C50[];
extern char _gp[];

int sceMc2End(void);
int CreateSema(struct SemaParam *p);
int CreateThread(struct ThreadParam *p);
int StartThread(int thid, void *arg);
int _sceMcCoreInit(void);
int _sceMcpInit(void);
int _sceMcFatInit(void);
void func_0011B458(void *arg);

int sceMc2Init(void) {
    struct ThreadParam tp;
    struct ThreadParam tp2;
    struct SemaParam sp;

    if (D_00135630[0] == 1) sceMc2End();
    sp.option = (unsigned int)D_00138C10;
    D_00151E2C[0] = -1;
    D_00151E20.thid = -1;
    D_00151E20.sema0 = -1;
    D_00151E20.sema1 = -1;
    sp.initCount = 1;
    sp.maxCount = 0x7F;
    D_00151E2C[0] = CreateSema(&sp);
    if (D_00151E2C[0] < 0) goto fail;
    sp.initCount = 0;
    sp.maxCount = 0x7F;
    sp.option = (unsigned int)D_00138C28;
    D_00151E20.sema0 = CreateSema(&sp);
    if (D_00151E20.sema0 < 0) goto fail;
    sp.maxCount = 0x7F;
    sp.option = (unsigned int)D_00138C40;
    sp.initCount = 0;
    D_00151E20.sema1 = CreateSema(&sp);
    if (D_00151E20.sema1 < 0) goto fail;
    D_00151904[0] = 0;
    tp.func = func_0011B458;
    tp.stack = D_00151E40;
    tp.stackSize = 0xC000;
    tp.gpReg = _gp;
    tp.option = (unsigned int)D_00138C50;
    tp.initPriority = 1;
    D_00151E20.thid = CreateThread(&tp);
    if (D_00151E20.thid < 0) {
        D_00135630[0] = 1;
        sceMc2End();
        return 0x81018004;
    }
    if (_sceMcCoreInit() == 0) goto fail;
    _sceMcpInit();
    _sceMcFatInit();
    StartThread(D_00151E20.thid, 0);
    D_00135630[0] = 1;
    return 0;
fail:
    D_00135630[0] = 1;
    sceMc2End();
    return 0x81018003;
}
