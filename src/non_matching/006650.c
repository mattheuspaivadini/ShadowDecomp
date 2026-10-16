/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 15 [cc=296].
 * R4 w25a_0: 64-bit ~0x1FF mask + 0x8000<<17
 * The original .s stays in the build (asm/cod/006650.s); this C
 * draft (Session 8) is kept for the record. */
extern int   D_00132070[];  /* .data GS packet, address ORed with 0x20000000 */
extern short SCREEN_WIDTH;    /* .sdata %gp_rel (lh) */
extern short SCREEN_HEIGHT;    /* .sdata %gp_rel (lh) */

void sceGsSetDefDrawEnv(void *p, short a1, short a2, short a3, short a4, short a5);
void sceGsSyncPath(int a0, int a1);
void sceGsPutDrawEnv(void *env);

void SetTexDrawEnvironment(int a0) {
    long long *p;
    long long *q;
    long long  v;

    p = (long long *)((unsigned int)D_00132070 | 0x20000000);
    q = p + 2;
    sceGsSetDefDrawEnv(q, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1, 0x31);
    v = q[0];
    v &= ~0x1FF;
    v |= (a0 / 32) & 0x1FF;
    q[0] = v;
    p[4] |= 0x100000000LL;
    sceGsSyncPath(0, 0);
    sceGsPutDrawEnv(p);
}
