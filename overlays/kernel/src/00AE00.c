/* KERNEL.XFF @ 0x00AE00 (320 B) - func_00AE00 (static, no symbol in the shipped .symtab)
 * STATUS: MATCHING [-G0 -fno-strict-aliasing]
 * Evidence: dldException report path. Walks executableModuleGroup with isysGroupForFirst/Next;
 *   for each group entry the static at .text+0xABF8 is asked to resolve the call address `pc`
 *   into a module/function name pair (two 0x100 stack buffers). The last tried module object is
 *   released with isysGroupForExit. A non-zero result is printed: result 2 prints the full
 *   "dldexception: __exception:" block (.rodata+0xCD8 with %p, +0xD28, +0xD88, +0xDD8 with %p,
 *   +0xE30 with two %p), then always .rodata+0xE70 (call address + module + function name);
 *   result 0 prints .rodata+0xEF0 ("Sorry, Infomation could't search."). The strings were read
 *   from the .rodata bytes to fix the argument counts.
 *   Callers: func_00B1C8 (tail call with the call site `ra - 8`).
 *   Shapes that mattered: the name buffer pointer is kept in a callee-saved register
 *   (`char *p = module;` -> `daddu $s4,$sp,$zero`), `int r` declared before the module object
 *   (fixes the $s2/$s3 roles), and the call result goes through a loop-local temp whose
 *   assignment to `r` sits in the break path (`t = f(); if (t) { r = t; break; }`), which is
 *   what makes the branch test $v0 and the copy land after it.
 * Levers tried (negatives): plain `if ((r = f()) != 0) break;` (3/80: copy before the branch),
 *   separate `r = f(); if (r)` (same), while/do-while/for(;;)/continue forms (same 3 words),
 *   one 0x200 buffer with `buf + 0x100` (63/80), no name-pointer local (36/80, $s4 unused),
 *   -fno-schedule-insns (64/80), -fno-schedule-insns2 (18/80), -fno-delayed-branch (57/80),
 *   -fno-gcse / -fno-cse-follow-jumps / -fno-optimize-sibling-calls (3/80, no change).
 * UNCONFIRMED: static prototype (void *pc); GroupEnt holds the module object at offset 0;
 *   the 0x100 buffers are `char[0x100]` (only their addresses are taken).
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
int LoaderSysPrintf(const char *fmt, ...);
extern char D_kernel_rodata_0CD8[];
extern char D_kernel_rodata_0D28[];
extern char D_kernel_rodata_0D88[];
extern char D_kernel_rodata_0DD8[];
extern char D_kernel_rodata_0E30[];
extern char D_kernel_rodata_0E70[];
extern char D_kernel_rodata_0EF0[];

void func_00AE00(void *pc) {
    char module[0x100];
    char func[0x100];
    char *p = module;
    struct GroupEnt *g;
    int r = 0;
    struct ModuleObj *m = 0;
    int t;

    for (g = isysGroupForFirst(executableModuleGroup, 0); g != 0; g = isysGroupForNext(g, 0)) {
        m = g->obj;
        t = func_00ABF8(p, func, m, pc);
        if (t != 0) {
            r = t;
            break;
        }
    }
    if (m != 0) {
        isysGroupForExit(m, 0);
    }
    if (r != 0) {
        if (r == 2) {
            LoaderSysPrintf(D_kernel_rodata_0CD8, pc);
            LoaderSysPrintf(D_kernel_rodata_0D28);
            LoaderSysPrintf(D_kernel_rodata_0D88);
            LoaderSysPrintf(D_kernel_rodata_0DD8, pc);
            LoaderSysPrintf(D_kernel_rodata_0E30, pc, pc);
        }
        LoaderSysPrintf(D_kernel_rodata_0E70, pc, module, func);
    } else {
        LoaderSysPrintf(D_kernel_rodata_0EF0, pc);
    }
}
