/* asm/cod/013F10.s -> SCE_GS_SET_TEX0.
 * sceGsSetDefTexEnv; sceGsTexEnv struct + SCE_GS_SET_TEX0/TEX1/CLAMP macros in field order (Session 22)
 * MATCHED. */
typedef unsigned long u_long;
typedef struct {
    u_long texflush;        /* 0x00 */
    u_long texflushaddr;    /* 0x08 */
    u_long tex11;           /* 0x10 */
    u_long tex11addr;       /* 0x18 */
    u_long tex01;           /* 0x20 */
    u_long tex01addr;       /* 0x28 */
    u_long clamp1;          /* 0x30 */
    u_long clamp1addr;      /* 0x38 */
} sceGsTexEnv;

#define SCE_GS_TEX0_1    0x06
#define SCE_GS_CLAMP_1   0x08
#define SCE_GS_TEX1_1    0x14
#define SCE_GS_TEXFLUSH  0x3f
#define SCE_GS_NOP       0x7f
#define SCE_GS_SET_TEX0(tbp, tbw, psm, tw, th, tcc, tfx, cbp, cpsm, csm, csa, cld)     ((u_long)(tbp) | ((u_long)(tbw) << 14) | ((u_long)(psm) << 20) |      ((u_long)(tw) << 26) | ((u_long)(th) << 30) | ((u_long)(tcc) << 34) |      ((u_long)(tfx) << 35) | ((u_long)(cbp) << 37) | ((u_long)(cpsm) << 51) |      ((u_long)(csm) << 55) | ((u_long)(csa) << 56) | ((u_long)(cld) << 61))
#define SCE_GS_SET_TEX1(lcm, mxl, mmag, mmin, mtba, l, k)     ((u_long)(lcm) | ((u_long)(mxl) << 2) | ((u_long)(mmag) << 5) |      ((u_long)(mmin) << 6) | ((u_long)(mtba) << 9) | ((u_long)(l) << 19) |      ((u_long)(k) << 32))
#define SCE_GS_SET_CLAMP(wms, wmt, minu, maxu, minv, maxv)     ((u_long)(wms) | ((u_long)(wmt) << 2) | ((u_long)(minu) << 4) |      ((u_long)(maxu) << 14) | ((u_long)(minv) << 24) | ((u_long)(maxv) << 34))

int sceGsSetDefTexEnv(sceGsTexEnv *tp, short flush, short tbp0, short tbw, short psm, short w, short h, short tfx, short cbp, short cpsm, short cld, short filter) {
    if (flush)
        tp->texflushaddr = SCE_GS_TEXFLUSH;
    else
        tp->texflushaddr = SCE_GS_NOP;
    tp->texflush = 0;
    tp->tex01addr = SCE_GS_TEX0_1;
    tp->tex01 = SCE_GS_SET_TEX0(tbp0, tbw, psm, w, h, 1, tfx, cbp, cpsm, 0, 0, cld);
    tp->tex11addr = SCE_GS_TEX1_1;
    tp->tex11 = SCE_GS_SET_TEX1(0, 0, filter & 1, filter, 0, 0, 0);
    tp->clamp1addr = SCE_GS_CLAMP_1;
    tp->clamp1 = SCE_GS_SET_CLAMP(1, 1, 0, 0, 0, 0);
    __asm__ __volatile__("sync" ::: "memory");
    return 4;
}
