/* STATUS (Session 23, 2026-10-18): NON_MATCHING. best score 11 [cc=29].
 * void function + void tail-callee (cc=29 tail j), typed MR record; residual = $v0/$v1 roles of the record base vs the uncached buffer (permute_stmts 500: no gain)
 * The original .s stays in the build (asm/cod/0198B8.s); this C
 * draft (Session 23) is kept for the record. * Session 23 step 3: permute_types.py --pairs --locals (struct members, externs, locals and parameters) - all variants tie, so the residual is not type-driven.
 */
struct MR { int active; void *buf; int size; int f0C; int f10; };
struct Pkt { char hdr[0x10]; int f10; int f14; };
extern int D_00135618 __attribute__((section(".data")));
extern struct MR D_001518C0;
extern char D_001510C0[];
void DIntr(void);
void EIntr(void);
void sceSifAddCmdHandler(int id, void (*fn)(void), void *arg);
int sceSifSendCmd(int id, void *pkt, int size, void *src, void *dst, int n);
int sceSifGetSreg(int reg);
void sceSifAddRebootNotifyHandler(int id, void (*fn)(int), void *arg);
void func_00119AC0(void);
void func_001199A0(int a0);

void sceSifMInitRpc(void) {
    struct Pkt *pkt;
    if (D_00135618 != 0) return;
    D_00135618 = 1;
    DIntr();
    D_001518C0.size = 0x20;
    D_001518C0.active = 1;
    D_001518C0.buf = (void *)((int)D_001510C0 | 0x20000000);
    D_001518C0.f0C = 0;
    D_001518C0.f10 = 0;
    sceSifAddCmdHandler(0x80000018, func_00119AC0, &D_001518C0);
    EIntr();
    pkt = (struct Pkt *)(D_001510C0 + 0x40);
    pkt->f14 = 1;
    pkt->f10 = 1;
    sceSifSendCmd(0x80000001, pkt, 0x18, 0, 0, 0);
    while (sceSifGetSreg(1) == 0)
        ;
    sceSifAddRebootNotifyHandler(0x80000014, func_001199A0, 0);
}
