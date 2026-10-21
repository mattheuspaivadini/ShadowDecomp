/* STATUS (Session 42, 2026-10-21): NON_MATCHING. best score 2 (was 6; sw.py diff lines).
 * moduleInfo.stack_size through an empty asm ("+r") fixes the move/lw order of the block-copy source; store order f14,f1C,f04,f0C,f10 (120-permutation grid). Residual: c+d addu issued before the f14 sum (the asm adds a cycle on the stack_size path). Tried: fence grids (+r / volatile use on a,b,c,d,s,info at every statement, 204 + 112 variants), sum temps with asm, a moduleInfo pointer local with asm x 120 store orders.
 * Residual = order of 'move a7,v0' vs 'lw 0x40(v0)' and of the two sums (a+b, c+d). Linker symbols via asm volatile (lui;nop;addiu;nop as in 001CC8). Tried all 120 orders of the five trailing stores, every position of the struct copy and of f04, unsigned/char * temporaries, unsigned stack_size/ModuleStackStart, a ModuleStackStart local; cc=29 changes size.
 * Session 30 (2026-10-19): still 4. Remaining = sched2 tie order: 'move a7,v0' (block-move source copy) must precede 'lw 0x40(v0)', and the f14 sum must precede c+d. Also tried: all 720 orders of the six trailing statements incl. the struct copy (best E14C0M = f14,f04,f1C,f0C,f10,copy), a moduleInfo pointer local (46+), char name[0x40] layout as in 0013C8, unsigned/void * info fields, int, unsigned, void * and char * for HeapStart and ModuleStackStart, -g0/-G0/-fno-strict-aliasing/-fno-schedule-insns{,2}.
 * Session 31 (2026-10-19): still 4. asm volatile memory barriers before/after each trailing statement: 45+ or size change (only after the copy keeps 4).
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
    { int s = moduleInfo.stack_size; asm("" : "+r"(s)); info->f14 = ModuleStackStart + s; }
    info->f1C = a;
    info->f04 = a + b;
    info->f0C = c + d;
    info->f10 = ModuleStackStart;
    info->module = moduleInfo;
    return 1;
}
