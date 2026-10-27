/* KERNEL.XFF @ 0x00A508 (240 B) - isysResolveAllModuleObjOfGroup
 * Evidence: walks the given group with isysGroupForFirst/Next and returns the number of objects visited (declaration order picks the image's register allocation). Module objects carry flag 0x20000000 in +0x2C once resolved: a fresh object gets static .text+0x77D8(obj, 1) and the flag; a flagged one is re-resolved with (obj, 0) only when static .text+0x7DC8(obj) reports undefined symbols. Each pass is timed with iosResetCpuRapCounter(2)/iosGetCpuRapCountPar1Int(). The walk ends with isysGroupForExit on the last object. UNCONFIRMED: names, static prototypes.
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

int isysResolveAllModuleObjOfGroup(void *group) {
    struct GroupEnt *g;
    int undef;
    int n = 0;
    struct ModuleObj *m = 0;

    for (g = isysGroupForFirst(group, 0); g != 0; g = isysGroupForNext(g, 0)) {
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
        n++;
    }
    if (m) {
        isysGroupForExit(m, 0);
    }
    return n;
}
