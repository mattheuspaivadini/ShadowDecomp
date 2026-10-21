/* asm/cod/005CE0.s -> ReinitDisp.
 * ReinitDisp; DMA/GS reset, mode argument through an empty asm (Session 42)
 * MATCHED. */
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
    { short z = 0; asm("" : "+r"(z)); sceGsResetGraph(z, 1, 2, 0); }    /* mode 0 issued after the other arguments */
    sceGsSetDefDBuff(&D_0013EB60, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 2, 0, 1);
    sceGsSyncV(0);
    D_0013A138 = 0;
    FlushCache(0);
    sceGsSwapDBuff(&D_0013EB60, D_0013A138);
    while (sceGsSyncPath(1, 0))
        scePrintf(D_00137C60);
}
