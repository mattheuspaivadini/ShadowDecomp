/* STATUS (Session 29, 2026-10-18): NON_MATCHING. best score 4 [cc=296].
 * Residual = 'move a0,zero' for sceGsResetGraph is scheduled before the SCREEN_WIDTH/HEIGHT stores (original: after). Tried int/short for all 16 parameter combinations, swapped stores, short SCREEN_*, a zero local; cc=29 changes size.
 * Session 30 (2026-10-19): still 4. Haifa sched2 (-fsched-verbose) shows the whole function is one block and the four argument loads tie on priority, so LUID order (a0 first) wins; the original issues a0 last. Also tried: K&R and variadic prototypes, a 64-bit first parameter, (short)/0L/0U/char/short/long zero arguments, side effects inside each argument, inline wrappers with parameters, volatile/unsigned SCREEN_*, NOTHROW_STUB on sceGsSyncV/sceGsResetPath/sceDmaGetChan (measurement only), wine 2.95.3 (60).
 * The original .s stays in the build (asm/cod/005CE0.s); this C
 * draft (Session 29) is kept for the record. */
typedef struct {
    unsigned int chcr;          /* 0x00 */
} sceDmaChan;

struct DBuff;

extern int SCREEN_WIDTH;        /* .sdata %gp_rel */
extern int SCREEN_HEIGHT;       /* .sdata %gp_rel */
extern int D_0013A138;          /* double-buffer index */
extern struct DBuff D_0013EB60;
extern char D_00137C60[];

int sceGsSyncV(int mode);
int sceDmaReset(int mode);
sceDmaChan *sceDmaGetChan(int id);
int sceDmaSync(sceDmaChan *d, int mode, int timeout);
void sceGsResetPath(void);
void sceGsResetGraph(short mode, short inter, short omode, short ffmode);
void sceGsSetDefDBuff(struct DBuff *db, short psm, short w, short h, short ztest, short zpsm, short clear);
void FlushCache(int mode);
int sceGsSwapDBuff(struct DBuff *db, int id);
int sceGsSyncPath(int mode, unsigned short timeout);
int scePrintf(const char *fmt, ...);

void ReinitDisp(void) {
    sceGsSyncV(0);
    sceDmaReset(1);
    sceDmaSync(sceDmaGetChan(0), 0, 100);
    sceDmaSync(sceDmaGetChan(1), 0, 100);
    sceDmaSync(sceDmaGetChan(2), 0, 100);
    sceDmaGetChan(0)->chcr |= 0x40;
    sceDmaGetChan(1)->chcr |= 0x40;
    sceDmaGetChan(2)->chcr |= 0x40;
    sceGsResetPath();
    sceGsSyncV(0);
    SCREEN_WIDTH = 640;
    SCREEN_HEIGHT = 448;
    sceGsResetGraph(0, 1, 2, 0);
    sceGsSetDefDBuff(&D_0013EB60, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 2, 0, 1);
    sceGsSyncV(0);
    D_0013A138 = 0;
    FlushCache(0);
    sceGsSwapDBuff(&D_0013EB60, D_0013A138);
    while (sceGsSyncPath(1, 0))
        scePrintf(D_00137C60);
}
