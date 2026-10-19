/* asm/cod/005408.s -> PutFont.
 * PutFont; SetPrimColor body expanded inline (packet through a pointer local), glyph bits/positions set up after it, 8x8 XYZ2 pairs on a scratchpad VIF1 packet (Session 35)
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
extern unsigned int D_0013A148; /* RGBAQ.Q bits */
extern u_long128 D_00137C40;    /* GIF tag */

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

extern int D_0013A150;
extern int D_0013A154;
extern int D_0013A158;
extern unsigned char D_00137440[];  /* 8x8 font bitmap, 8 bytes per glyph */
extern u_long128 D_00132240;        /* GIF tag (XYZ2 pairs) */

/* Same body as SetPrimColor (006898); the original expands it in place. */
static __inline__ void SetPrimColor(int prim, int r, int g, int b, int a) {
    sceVif1Packet pkt;
    sceVif1Packet *pk = &pkt;
    sceDmaChan *ch;

    sceVif1PkInit(pk, (u_long128 *)((D_0013A144 << 13) | 0x70000000));
    sceVif1PkReset(pk);
    sceVif1PkCnt(pk, 0);
    sceVif1PkOpenDirectCode(pk, 0);
    D_0013A144 = (D_0013A144 + 1) & 1;
    sceVif1PkOpenGifTag(pk, D_00137C40);
    sceVif1PkAddGsData(pk, prim | 0x40);
    sceVif1PkAddGsData(pk, (unsigned long)r | ((unsigned long)g << 8) | ((unsigned long)b << 16)
                       | ((unsigned long)a << 24) | ((unsigned long)D_0013A148 << 32));
    sceVif1PkCloseGifTag(pk);
    sceVif1PkCloseDirectCode(pk);
    sceVif1PkEnd(pk, 0);
    sceVif1PkTerminate(pk);
    sceGsSyncPath(0, 0);
    ch = sceDmaGetChan(1);
    ch->chcr |= 0x40;
    sceDmaSend(ch, (void *)(((unsigned int)pk->pBase & 0x3FF0) | 0x80000000));
}

void PutFont(int c, int x, int y)
{
    sceVif1Packet pk;
    sceDmaChan *ch;
    unsigned char *bits;
    int i, j;
    int px, py;

    SetPrimColor(0, D_0013A150, D_0013A154, D_0013A158, 0x80);
    bits = &D_00137440[c * 8];
    px = x << 4;
    py = (y << 4) + 0x8000;
    sceVif1PkInit(&pk, (u_long128 *)((D_0013A144 << 13) | 0x70000000));
    sceVif1PkReset(&pk);
    sceVif1PkCnt(&pk, 0);
    sceVif1PkOpenDirectCode(&pk, 0);
    D_0013A144 = (D_0013A144 + 1) & 1;
    sceVif1PkOpenGifTag(&pk, D_00132240);
    for (i = 0; i < 8; i++, bits++, py += 16) {
        for (j = 0; j < 8; j++) {
            if ((*bits >> j) & 1) {
                sceVif1PkAddGsData(&pk, (unsigned long)(0x8000 + px + j * 16) | ((unsigned long)py << 16)
                                   | ((unsigned long)0x800000 << 32));
                sceVif1PkAddGsData(&pk, (unsigned long)(0x8000 + px + j * 16) | ((unsigned long)(py - 16) << 16)
                                   | ((unsigned long)0x800000 << 32));
            }
        }
    }
    sceVif1PkCloseGifTag(&pk);
    sceVif1PkCloseDirectCode(&pk);
    sceVif1PkEnd(&pk, 0);
    sceVif1PkTerminate(&pk);
    sceGsSyncPath(0, 0);
    ch = sceDmaGetChan(1);
    ch->chcr |= 0x40;
    sceDmaSend(ch, (void *)(((unsigned int)pk.pBase & 0x3FF0) | 0x80000000));
}
