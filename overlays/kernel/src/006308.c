/* KERNEL.XFF @ 0x006308 (356 B) - func_006308 (static, no symbol in the shipped .symtab)
 * STATUS: MATCHING [-G0 -fno-strict-aliasing]
 * Closed by the supervisor: pinning the flag test to $v1 (`register ... asm("$3")`)
 * gives the image's andi destination, and reorg then annuls the slot (beql).
 * Previous residual (3/89):
 * Residual (+0x104,+0x108,+0x10c): image `lw $v1,0x18($s0); andi $v1,$v1,1;
 * beql $v1,$zero,skip` vs ours `lw $v0,...; andi $v0,...; beqz $v0,skip`.
 * Same CFG, same slot (`lui $v1,%hi(.bss)` + a second copy on the free path);
 * only the andi destination ($v1 vs $v0, local-alloc) and the dbr annul bit
 * (beql vs beqz) differ. Read as the reorg/dbr "annul" class (see
 * docs/archive-context-boot-elf.md s28/s29): not flag-controllable.
 *
 * Evidence:
 *  - iosCreateThread(..., .text+0x6308, ...) in 0x64670 iosInitThreadSystem makes
 *    this the manager-thread entry; .bss layout (thread table 0xB1A0, free list
 *    0xB5A0, used list 0xB5A4, request slot 0xD5C0, sema 0xD5C4, thread ptr
 *    0xD5B4, callback fn/arg 0xD5B8/0xD5BC) is fixed by 0x648A8 ioCallBackThreadMgr,
 *    0x64830 iosDeleteThread and 0x6470 iosInitThreadSystem.
 *  - relocations: iosCreateSema(1,1,0) -> .bss+0xD5C4; SleepThread(); state 0 =
 *    unlink the thread from the used list and push it on the free list after
 *    TerminateThread/DeleteThread/LoaderSysDeleteExternalThreadList and
 *    `if (flags & 1) iosFree(param->+8)`; state 1 = call the (fn,arg) slot;
 *    default = iosJumpRecoverPoint(.rodata+0x8D8); SignalSema(sema) then loop.
 *  - Dispatch is a switch on .bss+0xD5C0: cases laid out in source order
 *    (case 0 body, case 1 body, default) before the SignalSema join - the
 *    if/else-if/else spelling puts the body inline and never matched.
 *  - The callback takes ONE argument (a 1-arg prototype): that is what moves
 *    the `&used_list` address computation into the branch delay slot
 *    (19/89 -> 3/89). A 2-arg callback breaks 4 other words.
 *  - Store of the sema id goes through an address held in a register
 *    (`int *p = &D_kernel_bss_D5C4; *p = iosCreateSema(...)`): the image has
 *    `addiu $a0,$s2,-0x2A3C; sw $v0,0($a0)`, not a %lo displacement store.
 *
 * Levers tried (all scored, all gave 3/89 unless noted):
 *  - plain global store / local + store / pointer-store (19 -> 3 with pointer).
 *  - switch vs if / else-if / nested if (67, 68 diffs).
 *  - prev/next load order (image loads next first; pn spelling 5/89).
 *  - `& 1`, `(x&1)!=0`, `!(x&1)` else, `==0` + goto, `x % 2`, `1 & x`,
 *    ternary, char* cast, deferred pointer local, uid/table-clear reorderings:
 *    every one stays at 3/89 (statement order of the image is confirmed).
 *  - NOTHROW_STUB weak stubs for iosFree (and the whole callee set): no change.
 *  - cc=29: 64/89 and 20 B short (wrong compiler for this function).
 *  - -g0: identical; -fno-schedule-insns2: 43/89; -fno-gcse: 57/89 (+size).
 *
 * UNCONFIRMED: names/roles of the .bss objects and the thread struct fields
 * (uid/id/param/callback at +0xC/flags +0x18/prev +0x1C/next +0x20 re-derived
 * here from this function); ThreadParam.un8 is "the pointer freed when flag
 * bit 0 is set" (matches iosCreateThreadS setting that bit after its own
 * allocation); iosCreateSema's third argument is passed as 0 and unused here.
 */
struct ThreadParam {
    char pad0[8];
    void *unk8;
    char padC[0x24];
};
struct IosThread {
    int uid;
    int id;
    struct ThreadParam *param;
    void (*callback)(struct IosThread *);
    char pad10[8];
    unsigned int flags;
    struct IosThread *prev;
    struct IosThread *next;
    char pad24[8];
};
extern struct IosThread *D_kernel_bss_B1A0[256];
extern struct IosThread *D_kernel_bss_B5A0;
extern struct IosThread *D_kernel_bss_B5A4;
extern struct IosThread *D_kernel_bss_D5B0;
extern struct IosThread *D_kernel_bss_D5B4;
extern int D_kernel_bss_D5C0;
extern int D_kernel_bss_D5C4;
extern int D_kernel_bss_D5B8;
extern int D_kernel_bss_D5BC;
extern char D_kernel_rodata_08D8[];
int iosCreateSema(int init, int max, int opt);
void SleepThread(void);
int SignalSema(int sema);
void TerminateThread(int id);
void DeleteThread(int id);
void LoaderSysDeleteExternalThreadList(int id);
void iosFree(void *p);
void iosJumpRecoverPoint(const char *fmt, ...);

void func_006308(void) {
    struct IosThread *th;
    struct IosThread *next;
    struct IosThread *prev;
    int id;
    int *sema = &D_kernel_bss_D5C4;

    *sema = iosCreateSema(1, 1, 0);
    for (;;) {
        SleepThread();
        switch (D_kernel_bss_D5C0) {
        case 0:
            th = D_kernel_bss_D5B4;
            if (th->callback != 0) {
                th->callback(th);
            }
            id = th->id;
            next = th->next;
            prev = th->prev;
            if (th == D_kernel_bss_B5A4) {
                D_kernel_bss_B5A4 = next;
            }
            if (prev != 0) {
                prev->next = next;
            }
            if (next != 0) {
                next->prev = prev;
            }
            th->prev = 0;
            th->next = D_kernel_bss_B5A0;
            if (D_kernel_bss_B5A0 != 0) {
                D_kernel_bss_B5A0->prev = th;
            }
            D_kernel_bss_B5A0 = th;
            TerminateThread(id);
            DeleteThread(id);
            LoaderSysDeleteExternalThreadList(id);
            { register unsigned int f asm("$3") = th->flags & 1; if (f) {
                iosFree(th->param->unk8);
            }}
            th->uid = 0;
            D_kernel_bss_B1A0[id] = 0;
            break;
        case 1:
            ((void (*)(int))D_kernel_bss_D5B8)(D_kernel_bss_D5BC);
            break;
        default:
            iosJumpRecoverPoint(D_kernel_rodata_08D8);
            break;
        }
        SignalSema(D_kernel_bss_D5C4);
    }
}
