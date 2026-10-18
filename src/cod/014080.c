/* asm/cod/014080.s -> SCE_GS_SET_XYOFFSET.
 * sceGsSetHalfOffset; scissor bitfields + single SCE_GS_SET_XYOFFSET expression (Session 22)
 * MATCHED. */
typedef unsigned long u_long;
typedef struct {
    u_long SCAX0:11; u_long pad11:5;
    u_long SCAX1:11; u_long pad27:5;
    u_long SCAY0:11; u_long pad43:5;
    u_long SCAY1:11; u_long pad59:5;
} sceGsScissor;
typedef struct {
    char pad00[0x20];
    u_long xyoffset1;       /* 0x20 */
    u_long xyoffset1addr;   /* 0x28 */
    sceGsScissor scissor1;  /* 0x30 */
} sceGsDrawEnv1;
#define SCE_GS_SET_XYOFFSET(ofx, ofy) ((u_long)(ofx) | ((u_long)(ofy) << 32))

void sceGsSetHalfOffset(sceGsDrawEnv1 *draw, short centerx, short centery, short halfoff) {
    draw->xyoffset1 = SCE_GS_SET_XYOFFSET(((u_long)centerx - ((u_long)(draw->scissor1.SCAX1 + 1) >> 1)) << 4, (((u_long)centery - ((u_long)(draw->scissor1.SCAY1 + 1) >> 1)) << 4) + (halfoff ? 8 : 0));
}
