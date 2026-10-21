/* STATUS (Session 41, 2026-10-21): NON_MATCHING. best score 17 (was 35; sw.py diff lines).
 * Statement order found by a 360-permutation grid of the record stores x 120 packet-store orders (19 -> 14 instructions). Residual: register roles of the D_0014B140 / 0x20000000 / D_0014B000 values (image a0/v1/v0) and the f0C/f08 store slots. Tried cast types (int/unsigned) and f10/f14 field types, pkt derived from f10: no gain.
 * uncached packet base is |0x20000000 (fields 2/4/6/7/8) and f00 volatile (store+reload); residual = store scheduling of the record/packet fields (permute_stmts 400 variants: no gain)
 * The original .s stays in the build (asm/cod/0127E0.s); this C
 * draft (Session 23) is kept for the record. */
/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 23 [cc=29].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/0127E0.s); this C
 * draft (Session 9) is kept for the record. */
struct S0127E0 {
    volatile int f00;    /* 0x00 */
    int f04;    /* 0x04 */
    int f08;    /* 0x08 */
    int f0C;    /* 0x0C */
    int f10;    /* 0x10 */
    int f14;    /* 0x14 */
    int f18;    /* 0x18 */
};

struct P0127E0 {                 /* uncached packet at D_0014B000 | 0x20000002 */
    unsigned short f00;          /* 0x00 (untouched) */
    unsigned short f02;          /* 0x02 */
    unsigned short f04;          /* 0x04 */
    unsigned char  f06;          /* 0x06 */
    unsigned char  f07;          /* 0x07 */
    int            f08;          /* 0x08 */
};

extern struct S0127E0 D_0014AFD0;
extern int D_0014B000[];
extern int D_0014B140[];

int  FlushCache(int a0);
int  sceDeci2Open(int a0, int a1, int a2);
int  func_00112358(int a0);
void func_00112400(void);

int sceTtyInit(void) {
    struct P0127E0 *pkt;

    FlushCache(0);
    D_0014AFD0.f00 = sceDeci2Open(0x210, (int)&D_0014AFD0, (int)func_00112400);
    if (D_0014AFD0.f00 < 0)
        return 0;
    D_0014AFD0.f04 = 0;
    D_0014AFD0.f14 = (int)D_0014B140 | 0x20000000;
    pkt = (struct P0127E0 *)((int)D_0014B000 | 0x20000000);
    D_0014AFD0.f10 = (int)pkt;
    D_0014AFD0.f0C = 0;
    D_0014AFD0.f08 = 0;
    pkt->f04 = 0x210;
    pkt->f06 = 0x45;
    pkt->f07 = 0x48;
    pkt->f02 = 0;
    pkt->f08 = 0;
    D_0014AFD0.f18 = func_00112358(0x100);
    return 1;
}
