/* asm/cod/003110.s -> LoaderSysGetMemoryInfo.
 * Memory-map query; the info fields are addresses (char *), so their stores no longer alias the int
 * moduleInfo.stack_size load (the block-copy source copy then precedes that load); stores ordered
 * f10, f14, f1C, f04, f0C (Session 45)
 * MATCHED. */
struct LoaderModuleInfo {
    int  w[16];                 /* 0x00 */
    int  stack_size;            /* 0x40 UNCONFIRMED: added to ModuleStackStart */
    int  w44;                    /* 0x44 */
};

struct LoaderMemoryInfo {
    char *f00;                    /* 0x00 &D_1FE0000 */
    char *f04;                    /* 0x04 f00 + &D_20000 */
    char *f08;                    /* 0x08 &D_16A398 */
    char *f0C;                    /* 0x0C f08 + &D_40000 */
    char *f10;                    /* 0x10 ModuleStackStart */
    char *f14;                    /* 0x14 ModuleStackStart + stack_size */
    char *f18;                    /* 0x18 HeapStart */
    char *f1C;                    /* 0x1C &D_1FE0000 */
    struct LoaderModuleInfo module;   /* 0x20 */
};

extern int HeapStart;
extern int ModuleStackStart;
extern struct LoaderModuleInfo moduleInfo;

#define LA(var, sym) __asm__ volatile ("lui %0, %%hi(" #sym ")\n\tnop\n\taddiu %0, %0, %%lo(" #sym ")\n\tnop" : "=r" (var))

int LoaderSysGetMemoryInfo(struct LoaderMemoryInfo *info) {
    int a, b, c, d;

    info->f18 = (char *)HeapStart;
    LA(a, D_1FE0000);
    info->f00 = (char *)a;
    LA(b, D_20000);
    LA(c, D_16A398);
    info->f08 = (char *)c;
    LA(d, D_40000);
    info->f10 = (char *)ModuleStackStart;
    info->f14 = (char *)(ModuleStackStart + moduleInfo.stack_size);
    info->f1C = (char *)a;
    info->f04 = (char *)(a + b);
    info->f0C = (char *)(c + d);
    info->module = moduleInfo;
    return 1;
}
