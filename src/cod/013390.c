/* asm/cod/013390.s -> sceGsResetGraph.
 * libgraph reset by mode switch; GsPutIMR returns u_long (fixes the v0/v1 roles of the FFMode/VSCfunc pair) (Session 34)
 * MATCHED. */
typedef unsigned long u_long;
typedef struct {
    short sceGsInterMode;   /* 0x00 */
    short sceGsOutMode;
    short sceGsFFMode;
    short sceGsVersion;
    int (*sceGsVSCfunc)(void);  /* 0x08 */
    int sceGsVSCid;             /* 0x0C */
} sceGsGParam;

sceGsGParam *sceGsGetGParam(void);
u_long GsPutIMR(u_long imr);
int DisableIntc(int cause);
int RemoveIntcHandler(int cause, int hid);
void SetGsCrt(short interlace, short omode, short ffmode);
#define GS_CSR ((volatile u_long *)0x12001000)

void sceGsResetGraph(short mode, short inter, short omode, short ffmode) {
    sceGsGParam *gp;

    switch (mode) {
    case 0:
        gp = sceGsGetGParam();
        *GS_CSR = 0x200;
        gp->sceGsInterMode = inter;
        gp->sceGsOutMode = omode;
        gp->sceGsVersion = (*GS_CSR >> 16) & 0xFF;
        GsPutIMR(0xFF00);
        gp->sceGsFFMode = ffmode ? 1 : 0;
        if (gp->sceGsVSCfunc) {
            DisableIntc(2);
            RemoveIntcHandler(2, gp->sceGsVSCid);
            gp->sceGsVSCfunc = 0;
            gp->sceGsVSCid = 0;
        }
        SetGsCrt(inter & 1, omode & 0xFF, ffmode & 1);
        break;
    case 1:
        *GS_CSR = 0x100;
        break;
    case 5:
        gp = sceGsGetGParam();
        gp->sceGsInterMode = inter;
        gp->sceGsOutMode = omode;
        gp->sceGsFFMode = ffmode ? 1 : 0;
        gp->sceGsVersion = (*GS_CSR >> 16) & 0xFF;
        SetGsCrt(inter & 1, omode & 0xFF, ffmode & 1);
        break;
    }
}
