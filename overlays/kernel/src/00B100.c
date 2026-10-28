/* KERNEL.XFF @ 0x00B100 (192 B) - isysSearchCalledModuleFuncNameByAddr
 * Evidence: walks executableModuleGroup with isysGroupForFirst/Next; for each module object the static at .text+0xABF8 (module, func, obj, addr) is tried and the first non-zero result is kept (break); the walk ends with isysGroupForExit on the last object; returns the result (0 when not found). UNCONFIRMED: static prototype.
 */
struct ModuleObj;
struct GroupEnt {
    struct ModuleObj *obj;
};
extern char executableModuleGroup[];
struct GroupEnt *isysGroupForFirst(void *group, int arg);
struct GroupEnt *isysGroupForNext(struct GroupEnt *g, int arg);
void isysGroupForExit(struct ModuleObj *obj, int arg);
int func_00ABF8(char *module, char *func, struct ModuleObj *m, void *addr);

int isysSearchCalledModuleFuncNameByAddr(char *module, char *func, void *addr) {
    struct GroupEnt *g;
    struct ModuleObj *m = 0;
    int ret = 0;
    int r;

    for (g = isysGroupForFirst(executableModuleGroup, 0); g != 0; g = isysGroupForNext(g, 0)) {
        m = g->obj;
        r = func_00ABF8(module, func, m, addr);
        if (r) {
            ret = r;
            break;
        }
    }
    if (m) {
        isysGroupForExit(m, 0);
    }
    return ret;
}
