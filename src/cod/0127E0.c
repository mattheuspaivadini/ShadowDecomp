/* asm/cod/0127E0.s -> sceTtyInit.
 * SCE DECI2 sceTtyInit; record words f00..f0C volatile (their zero stores keep source order 0xC/4/8 ahead of the uncached-address ORs) (Session 44)
 * MATCHED. */
struct S0127E0 {                 /* DECI2 tty state; UNCONFIRMED: f00..f0C volatile because the handler shares them */
    volatile int f00;    /* 0x00 */
    volatile int f04;    /* 0x04 */
    volatile int f08;    /* 0x08 */
    volatile int f0C;    /* 0x0C */
    int f10;    /* 0x10 */
    int f14;    /* 0x14 */
    int f18;    /* 0x18 */
};

struct P0127E0 {                 /* uncached packet at D_0014B000 | 0x20000000 */
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
    D_0014AFD0.f0C = 0;
    D_0014AFD0.f04 = 0;
    D_0014AFD0.f08 = 0;
    D_0014AFD0.f14 = (int)D_0014B140 | 0x20000000;
    pkt = (struct P0127E0 *)((int)D_0014B000 | 0x20000000);
    D_0014AFD0.f10 = (int)pkt;
    pkt->f04 = 0x210;
    pkt->f06 = 0x45;
    pkt->f07 = 0x48;
    pkt->f02 = 0;
    pkt->f08 = 0;
    D_0014AFD0.f18 = func_00112358(0x100);
    return 1;
}
