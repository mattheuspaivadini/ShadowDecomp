/* asm/cod/013868.s -> sceGsSetDefDBuff.
 * sceGsSetDefDBuff; sceGsDBuff struct, GIF tag bitfields per tag, short half-zbuf local for DISPFB (Session 35)
 * MATCHED. */
typedef unsigned long u_long;
typedef unsigned int u_long128 __attribute__((mode(TI)));
typedef struct { short sceGsInterMode, sceGsOutMode, sceGsFFMode, sceGsVersion; } sceGsGParam;
typedef struct {
    u_long FBP:9; u_long FBW:6; u_long PSM:5; u_long pad00:12;
    u_long DBX:11; u_long DBY:11; u_long pad01:10;
} sceGsDispfb;
typedef struct {
    u_long pmode; u_long smode2; sceGsDispfb dispfb; u_long display; u_long bgcolor;
} sceGsDispEnv;
typedef struct {
    u_long NLOOP:15; u_long EOP:1; u_long pad16:16; u_long id:14; u_long PRE:1;
    u_long PRIM:11; u_long FLG:2; u_long NREG:4;
    u_long REGS0:4; u_long REGS1:4; u_long REGS2:4; u_long REGS3:4;
    u_long REGS4:4; u_long REGS5:4; u_long REGS6:4; u_long REGS7:4;
    u_long REGS8:4; u_long REGS9:4; u_long REGS10:4; u_long REGS11:4;
    u_long REGS12:4; u_long REGS13:4; u_long REGS14:4; u_long REGS15:4;
} sceGifTag __attribute__((aligned(16)));
typedef struct {
    u_long FBP:9; u_long pad09:7; u_long FBW:6; u_long pad22:2;
    u_long PSM:6; u_long pad30:2; u_long FBMSK:32;
} sceGsFrame;
typedef struct {
    sceGsFrame frame1; u_long frame1addr;
    u_long zbuf1; u_long zbuf1addr;
    u_long xyoffset1; u_long xyoffset1addr;
    u_long scissor1; u_long scissor1addr;
    u_long prmodecont; u_long prmodecontaddr;
    u_long colclamp; u_long colclampaddr;
    u_long dthe; u_long dtheaddr;
    u_long test1; u_long test1addr;
} sceGsDrawEnv1;
typedef struct { u_long w[12]; } sceGsClear;
typedef struct {
    sceGsDispEnv disp[2];
    sceGifTag giftag0;
    sceGsDrawEnv1 draw0;
    sceGsClear clear0;
    sceGifTag giftag1;
    sceGsDrawEnv1 draw1;
    sceGsClear clear1;
} sceGsDBuff;

#define SCE_GIF_CLEAR_TAG(tp) (*(u_long128 *)(tp) = (u_long128)0)

sceGsGParam *sceGsGetGParam(void);
void sceGsSetDefDispEnv(sceGsDispEnv *disp, short psm, short w, short h, short dx, short dy);
int sceGsSetDefDrawEnv(sceGsDrawEnv1 *draw, short psm, short w, short h, short ztest, short zpsm);
int sceGsSetDefClear(sceGsClear *cp, short ztest, short x, short y, short w, short h, int r, int g, int b, int a, unsigned int z);
short sceGszbufaddr(short psm, short w, short h);

void sceGsSetDefDBuff(sceGsDBuff *db, short psm, short w, short h, short ztest, short zpsm, short clear)
{
    sceGsGParam *gp;
    short zbuf;

    gp = sceGsGetGParam();
    sceGsSetDefDispEnv(&db->disp[0], psm, w, h, 0, 0);
    sceGsSetDefDispEnv(&db->disp[1], psm, w, h, 0, 0);
    sceGsSetDefDrawEnv(&db->draw0, psm, w, h, ztest, zpsm);
    sceGsSetDefDrawEnv(&db->draw1, psm, w, h, ztest, zpsm);
    if (clear) {
        sceGsSetDefClear(&db->clear0, ztest, 2048 - (w >> 1), 2048 - (h >> 1), w, h, 0, 0, 0, 0, 0);
        sceGsSetDefClear(&db->clear1, ztest, 2048 - (w >> 1), 2048 - (h >> 1), w, h, 0, 0, 0, 0, 0);
    }
    SCE_GIF_CLEAR_TAG(&db->giftag0);
    SCE_GIF_CLEAR_TAG(&db->giftag1);
    db->giftag0.NLOOP = clear ? 14 : 8;
    db->giftag0.EOP = 1;
    db->giftag0.NREG = 1;
    db->giftag0.REGS0 = 0xe;
    db->giftag1.NLOOP = clear ? 14 : 8;
    db->giftag1.EOP = 1;
    db->giftag1.NREG = 1;
    db->giftag1.REGS0 = 0xe;
    zbuf = sceGszbufaddr(psm, w, h);
    if ((*(u_long *)gp & 0xffff0000ffffUL) == 0x100000001UL || gp->sceGsInterMode == 0) {
        short half = zbuf >> 1;
        db->disp[1].dispfb.FBP = half;
        db->draw0.frame1.FBP = zbuf >> 1;
    }
}
