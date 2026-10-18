/* asm/cod/001D90.s -> execProgWithThread.
 * Plain (non-volatile) globals: the stack_size reload comes from int aliasing with D_00139E04; aligned stack kept in a local stored to D_00139E04 before req.stack, int-typed stack/gp_reg fields, gp_reg = (int)&_gp on an int _gp, align set right before use (Session 26).
 * MATCHED. */
struct Mod { char pad00[0x40]; int stack_size; };
struct ThreadParam { int status; void *func; int stack; int stack_size; int gp_reg; int init_priority; char pad18[0x18]; };
extern int D_00139E04;
extern int _gp;
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
    unsigned int st;

    m = func_001013C8();
    if (m == 0)
        return 0;
    func_001283D0(&req, 0, sizeof(req));
    req.func = _execProgWithThread;
    align = 0x10;
    st = ((unsigned int)D_00139E04 + align - 1) / align * align;
    D_00139E04 = st + m->stack_size;
    req.stack = (int)st;
    req.stack_size = m->stack_size;
    req.gp_reg = (int)&_gp;
    req.init_priority = prio;
    tmp = req;
    thid = CreateThread(&tmp);
    LoaderSysEntryExternalThreadList(thid);
    StartThread(thid, m);
    return (int)tmp.stack;
}
