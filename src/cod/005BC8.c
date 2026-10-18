/* asm/cod/005BC8.s -> Sync.
 * Sync; uncached double-buffer + alpha packet records, half-offset field read once before the branch (Session 23)
 * MATCHED. */
typedef unsigned long u_long;
struct DBuff { char pad000[0x50]; char giftag0[0x10]; char draw0[0xE0]; char giftag1[0x10]; char draw1[0x10]; };
struct AlphaPkt { u_long giftag[2]; u_long f10; u_long f18; u_long alpha[2]; };
extern int D_0013A138;
extern int D_0013A13C;
extern int D_0013A140;
extern struct DBuff D_0013EB60;
extern struct AlphaPkt D_001321A0;
int FlushCache(int mode);
int sceGsSyncPath(int mode, unsigned short timeout);
int sceGsSyncV(int mode);
int sceGsSwapDBuff(struct DBuff *db, int id);
int sceGsSetHalfOffset(void *draw, short x, short y, short half);
int sceGsPutDrawEnv(void *giftag);
int sceGsSetDefAlphaEnv(void *ap, short pctest);
#define UNCACHED(p) ((void *)((unsigned int)(p) | 0x20000000))

void Sync(void) {
    struct DBuff *db;
    struct AlphaPkt *ap;
    int half;

    FlushCache(0);
    sceGsSyncPath(1, 0);
    D_0013A140 = sceGsSyncV(0);
    D_0013A13C++;
    D_0013A138 = D_0013A13C & 1;
    sceGsSwapDBuff(&D_0013EB60, D_0013A138);
    db = UNCACHED(&D_0013EB60);
    half = D_0013A140;
    if (D_0013A138) {
        sceGsSetHalfOffset(db->draw1, 0x800, 0x800, half);
        sceGsPutDrawEnv(db->giftag1);
    } else {
        sceGsSetHalfOffset(db->draw0, 0x800, 0x800, half);
        sceGsPutDrawEnv(db->giftag0);
    }
    ap = UNCACHED(&D_001321A0);
    sceGsSetDefAlphaEnv(ap->alpha, 0);
    ap->alpha[0] = 0x44;
    ap->f10 = 0x20000;
    ap->f18 = 0x47;
    sceGsSyncPath(0, 0);
    sceGsPutDrawEnv(ap);
}
