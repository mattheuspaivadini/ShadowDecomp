/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 55 [cc=296].
 * R2 w45a_0: reg-alloc (real divu + two 0x30 struct locals)
 * The original .s stays in the build (asm/cod/001D90.s); this C
 * draft (Session 8) is kept for the record. */
extern int D_00139E04;

struct Ctx00101D90 {
    char pad[0x40];
    int  f40;       /* 0x40 */
};

struct Req00101D90 {
    int  f0;        /* 0x00 */
    int  f4;        /* 0x04 */
    int  f8;        /* 0x08 */
    int  fC;        /* 0x0C */
    int  f10;       /* 0x10 */
    int  f14;       /* 0x14 */
    char pad[0x18];
};

struct Ctx00101D90 *func_001013C8(void);
void func_001283D0(void *p, int a1, int a2);
void _execProgWithThread(int a0);
int  CreateThread(void *p);
void LoaderSysEntryExternalThreadList(int a0);
void StartThread(int a0, int a1);

int execProgWithThread(int a0, int a1) {
    struct Req00101D90 req;
    struct Req00101D90 tmp;
    struct Ctx00101D90 *p;
    int r;

    p = func_001013C8();
    if (p == 0)
        return 0;
    func_001283D0(&req, 0, 0x30);
    req.f4 = (int)_execProgWithThread;
    req.f8 = ((unsigned int)D_00139E04 + 0xF) / 0x10 * 0x10;
    D_00139E04 = req.f8 + p->f40;
    req.fC = p->f40;
    req.f10 = 0x00141D70;
    req.f14 = a1;
    tmp = req;
    r = CreateThread(&tmp);
    LoaderSysEntryExternalThreadList(r);
    StartThread(r, (int)p);
    return tmp.f8;
}
