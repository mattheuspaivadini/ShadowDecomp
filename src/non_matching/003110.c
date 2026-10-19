/* STATUS (Session 29, 2026-10-18): NON_MATCHING. best score 4 [cc=296].
 * Residual = order of 'move a7,v0' vs 'lw 0x40(v0)' and of the two sums (a+b, c+d). Linker symbols via asm volatile (lui;nop;addiu;nop as in 001CC8). Tried all 120 orders of the five trailing stores, every position of the struct copy and of f04, unsigned/char * temporaries, unsigned stack_size/ModuleStackStart, a ModuleStackStart local; cc=29 changes size.
 * The original .s stays in the build (asm/cod/003110.s); this C
 * draft (Session 29) is kept for the record. */
struct LoaderModuleInfo {
    int  w[16];                 /* 0x00 */
    int  stack_size;            /* 0x40 UNCONFIRMED: added to ModuleStackStart */
    int  w44;                   /* 0x44 */
};

struct LoaderMemoryInfo {
    int  f00;                   /* 0x00 &D_1FE0000 */
    int  f04;                   /* 0x04 f00 + &D_20000 */
    int  f08;                   /* 0x08 &D_16A398 */
    int  f0C;                   /* 0x0C f08 + &D_40000 */
    int  f10;                   /* 0x10 ModuleStackStart */
    int  f14;                   /* 0x14 ModuleStackStart + stack_size */
    int  f18;                   /* 0x18 HeapStart */
    int  f1C;                   /* 0x1C &D_1FE0000 */
    struct LoaderModuleInfo module;   /* 0x20 */
};

extern int HeapStart;
extern int ModuleStackStart;
extern struct LoaderModuleInfo moduleInfo;

#define LA(var, sym) __asm__ volatile ("lui %0, %%hi(" #sym ")\n\tnop\n\taddiu %0, %0, %%lo(" #sym ")\n\tnop" : "=r" (var))

int LoaderSysGetMemoryInfo(struct LoaderMemoryInfo *info) {
    int a, b, c, d;

    info->f18 = HeapStart;
    LA(a, D_1FE0000);
    info->f00 = a;
    LA(b, D_20000);
    LA(c, D_16A398);
    info->f08 = c;
    LA(d, D_40000);
    info->f14 = ModuleStackStart + moduleInfo.stack_size;
    info->f04 = a + b;
    info->f0C = c + d;
    info->f10 = ModuleStackStart;
    info->f1C = a;
    info->module = moduleInfo;
    return 1;
}
