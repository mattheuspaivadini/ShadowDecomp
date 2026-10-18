/* STATUS (Session 23, 2026-10-18): NON_MATCHING. best score 7 [cc=296] (was 55).
 * ThreadParam built at sp+0x30 and copied to sp (declaration order), runtime align divisor (divu), volatile heap pointer + stack_size give the reload. Residual = gp_reg store scheduled before mflo (permute_stmts 800: no gain).
 * The original .s stays in the build (asm/cod/001D90.s); this C
 * draft (Session 23) is kept for the record. */
struct Mod { char pad00[0x40]; volatile int stack_size; };
struct ThreadParam { int status; void *func; int stack; int stack_size; void *gp_reg; int init_priority; char pad18[0x18]; };
extern volatile int D_00139E04;
extern char _gp[];
struct Mod *func_001013C8(void);
void func_001283D0(void *p, int c, int n);   /* memset */
void _execProgWithThread(void *arg);
int CreateThread(struct ThreadParam *p);
int LoaderSysEntryExternalThreadList(int thid);
int StartThread(int thid, void *arg);

int execProgWithThread(int a0, int prio) {
    struct ThreadParam tmp;
    struct ThreadParam req;
    struct Mod *m;
    int align;
    int thid;

    m = func_001013C8();
    if (m == 0)
        return 0;
    func_001283D0(&req, 0, sizeof(req));
    align = 0x10;
    req.func = _execProgWithThread;
    req.stack = (int)(((unsigned int)D_00139E04 + align - 1) / align * align);
    D_00139E04 = (int)((int)req.stack + m->stack_size);
    req.stack_size = m->stack_size;
    req.gp_reg = _gp;
    req.init_priority = prio;
    tmp = req;
    thid = CreateThread(&tmp);
    LoaderSysEntryExternalThreadList(thid);
    StartThread(thid, m);
    return (int)tmp.stack;
}
