/* STATUS (Session 28, 2026-10-18): NON_MATCHING. best score 5 [cc=29].
 * First WaitSema reads csema through a volatile cast: a volatile load never enters a delay slot, which gives the original's unfilled jal slot (the final DeleteSema(cd->csema) stays plain and is slot-filled). Rec.f20 as void * fixes the option-pointer register (a1). Residual = r->cd/r->f20/r->f24 store vs cd->f10/cd->f24 load order (144-combination type grid over self/cd/f20/f24/f10 and permute_stmts: no gain).
 * The original .s stays in the build (asm/cod/019DD8.s); this C
 * draft (Session 28) is kept for the record. */
typedef struct { int count; int max_count; int init_count; int wait_threads; unsigned int attr; void *option; int pad[2]; } ee_sema_t;
struct CD;
struct Rec { char pad00[0x14]; int self; int f18; int cd; void * f20; int f24; char pad28[0x18]; };
struct CD { struct Rec * rec; int f04; volatile int sema; int f0C; int f10; char pad14[0x10]; int f24; int csema; volatile int f2C; };
extern char D_00138B28[];
extern int D_00138B70[];
extern char D_001518C0[];
void scePrintf(const char *fmt, ...);
int WaitSema(int s);
struct Rec *func_001199F8(void *pool);
int CreateSema(ee_sema_t *s);
void func_00119AA0(struct Rec *r);
int DeleteSema(int s);
int sceSifSendCmd(int id, void *pkt, int size, void *src, void *dst, int n);
int sceSifMUnBindRpc(struct CD *cd, int mode) {
    struct Rec *r;
    ee_sema_t s;
    int sema;

    if (mode != 0) {
        scePrintf(D_00138B28, mode);
        return -1;
    }
    WaitSema(((volatile struct CD *)cd)->csema);
    r = func_001199F8(D_001518C0);
    if (r == 0)
        return -1;
    cd->rec = r;
    cd->f04 = r->f18;
    r->self = (int)r;
    r->cd = (int)cd;
    r->f20 = (void *)cd->f10;
    r->f24 = (int)cd->f24;
    s.option = D_00138B70;
    s.init_count = 0;
    s.max_count = 1;
    cd->sema = CreateSema(&s);
    sema = cd->sema;
    if (sema < 0) {
        func_00119AA0(r);
        return -3;
    }
    if (sceSifSendCmd(0x8000001D, r, 0x40, 0, 0, 0) == 0) {
        func_00119AA0(r);
        DeleteSema(sema);
        return -2;
    }
    WaitSema(sema);
    DeleteSema(sema);
    if (cd->f2C == 1)
        DeleteSema(cd->csema);
    return cd->f2C;
}
