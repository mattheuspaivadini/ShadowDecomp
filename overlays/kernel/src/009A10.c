/* KERNEL.XFF @ 0x009A10 (244 B) - isysResolveAllProgramModule
 * Evidence: iosGetTCount(); walks the program-module group (.data+0x380) with isysGroupForFirst/Next; returns 1. Module objects carry flag 0x20000000 in +0x2C once resolved: a fresh object gets static .text+0x77D8(obj, 1) and the flag; a flagged one is re-resolved with (obj, 0) only when static .text+0x7DC8(obj) reports undefined symbols. Each pass is timed with iosResetCpuRapCounter(2)/iosGetCpuRapCountPar1Int(). The walk ends with isysGroupForExit on the last object. UNCONFIRMED: names, static prototypes.
 */
struct ModuleObj {
    char pad[0x2C];
    unsigned int flags;
};
struct GroupEnt {
    struct ModuleObj *obj;
};
unsigned long iosGetTCount(void);
struct GroupEnt *isysGroupForFirst(void *group, int arg);
struct GroupEnt *isysGroupForNext(struct GroupEnt *g, int arg);
void isysGroupForExit(struct ModuleObj *obj, int arg);
void iosResetCpuRapCounter(int n);
int iosGetCpuRapCountPar1Int(void);
static int func_007DC8(struct ModuleObj *m);
static void func_0077D8(struct ModuleObj *m, int first);
extern char D_kernel_data_0380[];

int isysResolveAllProgramModule(void) {
    struct GroupEnt *g;
    struct ModuleObj *m = 0;
    int undef;

    iosGetTCount();
    for (g = isysGroupForFirst(D_kernel_data_0380, 0); g != 0; g = isysGroupForNext(g, 0)) {
        m = g->obj;
        iosResetCpuRapCounter(2);
        undef = func_007DC8(m);
        iosGetCpuRapCountPar1Int();
        if (m->flags & 0x20000000) {
            if (undef) {
                func_0077D8(m, 0);
            }
        } else {
            func_0077D8(m, 1);
            m->flags |= 0x20000000;
        }
        iosGetCpuRapCountPar1Int();
    }
    if (m) {
        isysGroupForExit(m, 0);
    }
    return 1;
}
