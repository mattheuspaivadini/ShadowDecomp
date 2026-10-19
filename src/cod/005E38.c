/* asm/cod/005E38.s -> LoaderSysDrawSprite.
 * LoaderSysDrawSprite; SetPrimColorTex body expanded inline per branch, per-branch packet tail with a block-local DMA channel (Session 35)
 * MATCHED. */
typedef unsigned int u_long128 __attribute__((mode(TI)));

typedef struct {
    u_long128 *pCurrent;        /* 0x00 */
    u_long128 *pBase;           /* 0x04 */
    unsigned int *pDmaTag;      /* 0x08 */
    unsigned int *pVifCode;     /* 0x0C */
    unsigned int *pGifTag;      /* 0x10 */
    int pad[3];
} sceVif1Packet;

typedef struct {
    unsigned int chcr;          /* 0x00 */
} sceDmaChan;

extern int D_0013A144;          /* scratchpad double-buffer index */
extern unsigned int D_0013A14C; /* RGBAQ.Q bits */
extern u_long128 D_00137C50;    /* GIF tag */

void sceVif1PkInit(sceVif1Packet *pk, u_long128 *base);
void sceVif1PkReset(sceVif1Packet *pk);
void sceVif1PkCnt(sceVif1Packet *pk, unsigned int opt);
void sceVif1PkOpenDirectCode(sceVif1Packet *pk, int stall);
void sceVif1PkOpenGifTag(sceVif1Packet *pk, u_long128 gifTag);
void sceVif1PkAddGsData(sceVif1Packet *pk, unsigned long data);
void sceVif1PkCloseGifTag(sceVif1Packet *pk);
void sceVif1PkCloseDirectCode(sceVif1Packet *pk);
void sceVif1PkEnd(sceVif1Packet *pk, unsigned int opt);
void *sceVif1PkTerminate(sceVif1Packet *pk);
int sceGsSyncPath(int mode, unsigned short timeout);
sceDmaChan *sceDmaGetChan(int id);
void sceDmaSend(sceDmaChan *d, void *tag);

extern u_long128 D_00132250;    /* GIF tag: UV, XYZ2, UV, XYZ2 */
extern u_long128 D_00132260;    /* GIF tag: XYZ2, XYZ2 */

/* Same body as SetPrimColorTex (0069E8); the original expands it in place. */
static __inline__ void SetPrimColorTex(int prim, int r, int g, int b, int a, int ctxt) {
    sceVif1Packet pkt;
    sceVif1Packet *pk = &pkt;
    sceDmaChan *ch;
    unsigned long p;

    sceVif1PkInit(pk, (u_long128 *)((D_0013A144 << 13) | 0x70000000));
    sceVif1PkReset(pk);
    sceVif1PkCnt(pk, 0);
    sceVif1PkOpenDirectCode(pk, 0);
    D_0013A144 = (D_0013A144 + 1) & 1;
    sceVif1PkOpenGifTag(pk, D_00137C50);
    p = prim | 0x10;
    if (ctxt)
        p |= 0x100;
    sceVif1PkAddGsData(pk, p);
    sceVif1PkAddGsData(pk, (unsigned long)r | ((unsigned long)g << 8) | ((unsigned long)b << 16)
                       | ((unsigned long)a << 24) | ((unsigned long)D_0013A14C << 32));
    sceVif1PkCloseGifTag(pk);
    sceVif1PkCloseDirectCode(pk);
    sceVif1PkEnd(pk, 0);
    sceVif1PkTerminate(pk);
    sceGsSyncPath(0, 0);
    ch = sceDmaGetChan(1);
    ch->chcr |= 0x40;
    sceDmaSend(ch, (void *)(((unsigned int)pk->pBase & 0x3FF0) | 0x80000000));
}

#define XYZ2(x, y) ((unsigned long)(((x) + 0x800) << 4) | ((unsigned long)(((y) + 0x800) << 4) << 16) \
                    | ((unsigned long)0x800000 << 32))

void LoaderSysDrawSprite(int *xy, int *uv, int *rgba, int unused, int tex)
{
    sceVif1Packet pk;

    if (tex) {
        SetPrimColorTex(6, rgba[0], rgba[1], rgba[2], rgba[3], 1);
        sceVif1PkInit(&pk, (u_long128 *)((D_0013A144 << 13) | 0x70000000));
        sceVif1PkReset(&pk);
        sceVif1PkCnt(&pk, 0);
        sceVif1PkOpenDirectCode(&pk, 0);
        D_0013A144 = (D_0013A144 + 1) & 1;
        sceVif1PkOpenGifTag(&pk, D_00132250);
        sceVif1PkAddGsData(&pk, (unsigned long)uv[0] | ((unsigned long)uv[1] << 16));
        sceVif1PkAddGsData(&pk, XYZ2(xy[0], xy[1]));
        sceVif1PkAddGsData(&pk, (unsigned long)(uv[2] << 4) | ((unsigned long)(uv[3] << 4) << 16));
        sceVif1PkAddGsData(&pk, XYZ2(xy[2], xy[3]));
        sceVif1PkCloseGifTag(&pk);
        sceVif1PkCloseDirectCode(&pk);
        sceVif1PkEnd(&pk, 0);
        sceVif1PkTerminate(&pk);
        sceGsSyncPath(0, 0);
        {
            sceDmaChan *c = sceDmaGetChan(1);
            c->chcr |= 0x40;
            sceDmaSend(c, (void *)(((unsigned int)pk.pBase & 0x3FF0) | 0x80000000));
        }
    } else {
        SetPrimColorTex(6, rgba[0], rgba[1], rgba[2], rgba[3], 1);
        sceVif1PkInit(&pk, (u_long128 *)((D_0013A144 << 13) | 0x70000000));
        sceVif1PkReset(&pk);
        sceVif1PkCnt(&pk, 0);
        sceVif1PkOpenDirectCode(&pk, 0);
        D_0013A144 = (D_0013A144 + 1) & 1;
        sceVif1PkOpenGifTag(&pk, D_00132260);
        sceVif1PkAddGsData(&pk, XYZ2(xy[0], xy[1]));
        sceVif1PkAddGsData(&pk, XYZ2(xy[2], xy[3]));
        sceVif1PkCloseGifTag(&pk);
        sceVif1PkCloseDirectCode(&pk);
        sceVif1PkEnd(&pk, 0);
        sceVif1PkTerminate(&pk);
        sceGsSyncPath(0, 0);
        {
            sceDmaChan *c = sceDmaGetChan(1);
            c->chcr |= 0x40;
            sceDmaSend(c, (void *)(((unsigned int)pk.pBase & 0x3FF0) | 0x80000000));
        }
    }
}
