/* ARCHIVED (Session 63, 2026-10-24): codegen-tuned attempt for 0141B8,
 * kept as the matching reference (it is the closest C form: see the STATUS
 * below).  The build now uses src/cod/0141B8.c, an instruction-stream
 * transcription; the readable reconstruction is
 * src/non_matching/0141B8.c.
 */
/* STATUS (Session 46, 2026-10-22): NON_MATCHING. best score 114 (was 160; sw.py diff lines).
 * SCE_GS_SET_DISPLAY terms ORed as magh, dh, dw, magv, dy, dx (a 120-order grid; the image tree is ((MAGH|DW)|(DX|DH))|DY, explicit trees score worse) and DISPFB written as (psm << 15) | (fbw << 9). Residual: the magh*w / dx*magh multiply order and the magh copy in the display arms; callee return types (void scePrintf) change nothing.
 * sceGsSetDefDispEnv; OutMode if-chain (NTSC/PAL/0x50/else scePrintf), smode2 via nested if with
 * direct stores, DX offset added in 64 bits through a long local. Residual = the DISPLAY OR-tree
 * order (original combines MAGH|DW and DX|DH before DY) and register roles in the PAL/NTSC arms.
 * Tried: macro arg orders, (u_long)/(long) casts on the offset, ternary DH, void scePrintf,
 * cc=296.
 * The original .s stays in the build (asm/cod/0141B8.s); this C
 * draft (Session 35) is kept for the record. */
typedef unsigned long u_long;
typedef struct { short sceGsInterMode, sceGsOutMode, sceGsFFMode, sceGsVersion; } sceGsGParam;
typedef struct {
    u_long pmode; u_long smode2; u_long dispfb; u_long display; u_long bgcolor;
} sceGsDispEnv;

#define SCE_GS_SET_DISPFB(fbp, fbw, psm, dbx, dby) \
    ((u_long)(fbp) | ((u_long)(fbw) << 9) | ((u_long)(psm) << 15) | \
     ((u_long)(dbx) << 32) | ((u_long)(dby) << 43))
#define SCE_GS_SET_DISPLAY(dx, dy, magh, magv, dw, dh) (((u_long)(magh) << 23) | ((u_long)(dh) << 44) | ((u_long)(dw) << 32) | ((u_long)(magv) << 27) | ((u_long)(dy) << 12) | (u_long)(dx))

extern char D_001384B8[];
sceGsGParam *sceGsGetGParam(void);
int func_00114108(void);
void func_001141A8(short mode, int *a, int *b, int *c, int *d);
int scePrintf(const char *fmt, ...);

void sceGsSetDefDispEnv(sceGsDispEnv *disp, short psm, short w, short h, short dx, short dy)
{
    sceGsGParam *gp;
    int magh;
    int smode;
    u_long x0;
    int ofs[4];

    gp = sceGsGetGParam();
    if (gp->sceGsOutMode != 2 && gp->sceGsOutMode != 3 && func_00114108())
        func_001141A8(gp->sceGsOutMode, &ofs[0], &ofs[1], &ofs[2], &ofs[3]);
    else
        ofs[0] = ofs[1] = ofs[2] = ofs[3] = 0;
    disp->pmode = 0x66;
    if (gp->sceGsInterMode) {
        if (gp->sceGsFFMode == 0)
            disp->smode2 = 1;
        else
            disp->smode2 = 3;
    } else
        disp->smode2 = 2;
    disp->dispfb = ((u_long)(psm & 0xf) << 15) | ((u_long)(((w + 63) >> 6) & 0x3f) << 9);
    if (gp->sceGsOutMode == 2) {
        if (gp->sceGsInterMode == 1) {
            magh = (w + 2559) / w;
            x0 = (long)ofs[0] + 636;
            disp->display = SCE_GS_SET_DISPLAY((dx * magh + x0) & 0xfff, (dy + ofs[1] + 50) & 0xfff,
                                               magh - 1, 0, magh * w - 1, gp->sceGsFFMode ? h * 2 - 1 : h - 1);
        } else {
            magh = (w + 2559) / w;
            x0 = (long)ofs[0] + 636;
            disp->display = SCE_GS_SET_DISPLAY((dx * magh + x0) & 0xfff, (dy + ofs[1] + 25) & 0xfff,
                                               magh - 1, 0, magh * w - 1, h - 1);
        }
    } else if (gp->sceGsOutMode == 3) {
        if (gp->sceGsInterMode == 1) {
            magh = (w + 2559) / w;
            x0 = (long)ofs[0] + 656;
            disp->display = SCE_GS_SET_DISPLAY((dx * magh + x0) & 0xfff, (dy + ofs[1] + 72) & 0xfff,
                                               magh - 1, 0, magh * w - 1, gp->sceGsFFMode ? h * 2 - 1 : h - 1);
        } else {
            magh = (w + 2559) / w;
            x0 = (long)ofs[0] + 656;
            disp->display = SCE_GS_SET_DISPLAY((dx * magh + x0) & 0xfff, (dy + ofs[1] + 36) & 0xfff,
                                               magh - 1, 0, magh * w - 1, h - 1);
        }
    } else if (gp->sceGsOutMode == 0x50) {
        disp->display = SCE_GS_SET_DISPLAY(((720 - w) / 2 * 2 + ofs[0] + dx * 2 + 232) & 0xfff, (dy + ofs[1] + 35) & 0xfff,
                                           1, 0, w * 2 - 1, h - 1);
    } else {
        scePrintf(D_001384B8, gp->sceGsOutMode);
    }
    disp->bgcolor = 0;
}
