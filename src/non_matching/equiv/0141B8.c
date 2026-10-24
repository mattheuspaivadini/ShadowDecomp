/* C equivalent of sceGsSetDefDispEnv (0141B8, 884 B @ 0x001141B8).
 *
 * Reconstructed from asm/cod/0141B8.s and the REA/Ghidra Emotion Engine
 * dossier ev_2ce041e56a3fb1bb912193fcdffbc4476383383b6b8300490954cd7ee4c39783;
 * the GS register macros and the psm/mode enum follow the libgraph style used
 * by the matched 014020/014FF0.  Readable reconstruction: NOT byte-exact (130
 * diff instructions in the OR-tree order and the PAL/NTSC register roles), not
 * part of the build.  The codegen-tuned near-miss is
 * src/non_matching/0141B8.c.
 *
 * Builds a GS DISPFB/DISPLAY/SMODE2 environment for the current output mode.
 * The offsets returned by func_001141A8() are only fetched when the current
 * mode is not NTSC/PAL and the video mode is interlaced (func_00114108).
 *
 * Behaviour derived from the target:
 *   14210  lhu 0x2 / sltiu        -> sceGsOutMode is an unsigned 16-bit field
 *   14218  beqz                   -> mode 2/3 skip func_001141A8
 *   14264  lhu 0x0 + sll/sra      -> InterMode is read unsigned, sign-extended
 *   14270  lh 0x0                 -> the FFMode test uses a signed load
 *   142D8  div + break 7          -> magh = (w + 2559) / w
 *   14330  ...                    -> display = MAGH|DW|DX|DH then DY
 *   144A0  daddiu a3,a2,0xE8      -> the 0x50 (480P) arm works in 64 bits
 *   144D4  magh = 1 -> 0x800000   -> 480P forces MAGH = 0
 */
typedef unsigned long u_long;

typedef struct {
    unsigned short sceGsInterMode;  /* 0x00: 0 = progressive, 1 = interlaced */
    unsigned short sceGsOutMode;    /* 0x02: 2 = NTSC, 3 = PAL, 0x50 = 480P */
    unsigned short sceGsFFMode;     /* 0x04: field/frame (PAL/NTSC) */
    unsigned short sceGsVersion;    /* 0x06 */
} sceGsGParam;

typedef struct {
    u_long pmode;                   /* 0x00 */
    u_long smode2;                  /* 0x08 */
    u_long dispfb;                  /* 0x10 */
    u_long display;                 /* 0x18 */
    u_long bgcolor;                 /* 0x20 */
} sceGsDispEnv;

#define SCE_GS_SET_DISPFB(fbp, fbw, psm, dbx, dby)                  \
    ((u_long)(fbp) | ((u_long)(fbw) << 9) | ((u_long)(psm) << 15) | \
     ((u_long)(dbx) << 32) | ((u_long)(dby) << 43))

#define SCE_GS_SET_DISPLAY(dx, dy, magh, magv, dw, dh)                   \
    ((u_long)(dx) | ((u_long)(dy) << 12) | ((u_long)(magh) << 23) |      \
     ((u_long)(magv) << 27) | ((u_long)(dw) << 32) | ((u_long)(dh) << 44))

extern char D_001384B8[];           /* "sceGsSetDefDispEnv: unknown out mode %d\n" */

sceGsGParam *sceGsGetGParam(void);
int func_00114108(void);            /* UNCONFIRMED: interlaced video mode? */
void func_001141A8(short mode, int *a, int *b, int *c, int *d);
int scePrintf(const char *fmt, ...);

void sceGsSetDefDispEnv(sceGsDispEnv *disp, short psm, short w, short h,
                        short dx, short dy)
{
    sceGsGParam *gp;
    int magh;
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
    } else {
        disp->smode2 = 2;
    }
    disp->dispfb = SCE_GS_SET_DISPFB(0, (w + 63) >> 6, psm & 0xF, 0, 0);

    if (gp->sceGsOutMode == 2) {            /* NTSC */
        magh = (w + 2559) / w;
        x0 = (u_long)ofs[0] + 636;
        if (gp->sceGsInterMode == 1)
            disp->display = SCE_GS_SET_DISPLAY((dx * magh + x0) & 0xFFF,
                                               (dy + ofs[1] + 50) & 0xFFF,
                                               magh - 1, 0, magh * w - 1,
                                               gp->sceGsFFMode ? h * 2 - 1 : h - 1);
        else
            disp->display = SCE_GS_SET_DISPLAY((dx * magh + x0) & 0xFFF,
                                               (dy + ofs[1] + 25) & 0xFFF,
                                               magh - 1, 0, magh * w - 1, h - 1);
    } else if (gp->sceGsOutMode == 3) {     /* PAL */
        magh = (w + 2559) / w;
        x0 = (u_long)ofs[0] + 656;
        if (gp->sceGsInterMode == 1)
            disp->display = SCE_GS_SET_DISPLAY((dx * magh + x0) & 0xFFF,
                                               (dy + ofs[1] + 72) & 0xFFF,
                                               magh - 1, 0, magh * w - 1,
                                               gp->sceGsFFMode ? h * 2 - 1 : h - 1);
        else
            disp->display = SCE_GS_SET_DISPLAY((dx * magh + x0) & 0xFFF,
                                               (dy + ofs[1] + 36) & 0xFFF,
                                               magh - 1, 0, magh * w - 1, h - 1);
    } else if (gp->sceGsOutMode == 0x50) {  /* 480P: fixed magnification */
        u_long x = (u_long)ofs[0] + (u_long)((720 - w) / 2 * 2) +
                   (u_long)dx * 2 + 232;

        disp->display = SCE_GS_SET_DISPLAY(x & 0xFFF,
                                           (dy + ofs[1] + 35) & 0xFFF,
                                           1, 0, w * 2 - 1, h - 1);
    } else {
        scePrintf(D_001384B8, gp->sceGsOutMode);
    }
    disp->bgcolor = 0;
}
