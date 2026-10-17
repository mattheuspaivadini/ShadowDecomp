/* asm/cod/006650.s -> SetTexDrawEnvironment.
 * boot GS tex draw env; FBP field computed before the merge (Session 19)
 * MATCHED. */
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
    v = (a0 / 32) & 0x1FF;
    q[0] = (q[0] & ~0x1FF) | v;
    p[4] |= 0x100000000LL;
    sceGsSyncPath(0, 0);
    sceGsPutDrawEnv(p);
}
