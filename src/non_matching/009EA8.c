/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 50 [cc=29].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/009EA8.s); this C
 * draft (Session 9) is kept for the record. */
struct D009EA8 {
    char         pad00[0x4];
    int          f04;    /* 0x04  indirect call target */
    int          f08;    /* 0x08  source pointer */
    int          f0C;    /* 0x0C  source size */
    char         pad10[0xC];
    int          f1C;    /* 0x1C */
    int          f20;    /* 0x20 */
    int          f24;    /* 0x24  first callback argument */
    int          f28;    /* 0x28  second buffer pointer */
    int          f2C;    /* 0x2C  second buffer size */
    int          f30;    /* 0x30  selects the RPC path */
    unsigned int f34;    /* 0x34  bit 4 selects the pool routine */
};

struct P009EA8 {
    char pad10[0x10];
    int  f10;   /* 0x10 */
    int  f14;   /* 0x14 */
    int  f18;   /* 0x18 */
    int  f1C;   /* 0x1C */
    int  f20;   /* 0x20 */
};

extern int D_00145940[];

int sceSifWriteBackDCache(int a0, int a1);
int DIntr(void);
int EIntr(void);
int func_00109288(int a0, int a1);
int func_001092B8(int a0, int a1);
int sceSifSendCmd(int a0, int a1, int a2, int a3, int a4, int a5);
int sceSifSetDma(int a0, int a1);

void sceSifExecRequest(struct D009EA8 *p) {
    struct P009EA8 *pkt;
    int list[8];
    int data;
    int len;
    int n;
    int r;
    unsigned int t;

    len = 0;
    data = ((int (*)(int, int, int))p->f04)(p->f24, p->f08, p->f0C);
    if (data != 0)
        len = p->f2C;
    if (p->f0C > 0)
        sceSifWriteBackDCache(p->f08, p->f0C);
    if (len > 0)
        sceSifWriteBackDCache(data, len);
    DIntr();
    if (p->f34 & 4)
        pkt = (struct P009EA8 *)func_001092B8((int)D_00145940, p->f34 >> 16);
    else
        pkt = (struct P009EA8 *)func_00109288((int)D_00145940, p->f34 >> 16);
    EIntr();
    pkt->f20 = 0x8000000A;
    pkt->f1C = p->f1C;
    if (p->f30 != 0) {
        do {
            r = sceSifSendCmd(0x80000008, (int)pkt, 0x40, data, p->f28, len);
        } while (r == 0);
    } else {
        pkt->f18 = 0;
        pkt->f10 = 0;
        n = 0;
        if (len > 0) {
            n = 1;
            list[0] = data;
            list[1] = p->f28;
            list[2] = len;
            list[3] = 0;
        }
        list[4 * n + 0] = (int)pkt;
        list[4 * n + 1] = p->f20;
        list[4 * n + 2] = 0x40;
        list[4 * n + 3] = 0;
        n++;
        while (sceSifSetDma((int)list, n) == 0) {
            t = 0x000F0000;
            do {
                t--;
                __asm__ __volatile__("nop\n\tnop\n\tnop\n\tnop");
            } while (t != (unsigned int)-1);
        }
    }
}
