/* KERNEL.XFF @ 0x014EB0 (376 B) - iosGsSetDrawContext
 * Evidence: the two-entry .bss+0x1F010 bit-0/bit-5 copy loop (entries at
 * base+0x10, stride 0x38, flag word at +8, source bit base+0xA0), then
 * func_014BA0(), then the draw-context buffer word at +0x88 (second one at
 * +0x190 when iosDlGetWorkBufId() == 0), its GIF tag qword at +0x10 masked with
 * 0x7FFF plus 1 sent as QWC, the buffer address as MADR, FlushCache(0), GIF
 * CHCR = 0x141; the dsll32/dsrl32 on pkt, the `and` on the zero-extended value
 * and the two dsll32/dsra32 before the stores mean qwc is a signed 64-bit value
 * and the MADR expression is built in 64 bits then truncated.
 * The image keeps only %hi(.bss) in s0 and re-derives the full address with an
 * `addiu ... %lo` for the loop and again after the call: that is what a
 * `volatile` struct object plus a base pointer variable produces. The two flag
 * masks are locals assigned before the loop (their `li` precedes the loop-init
 * in the preheader) and `sel` is volatile (read twice per iteration).
 * UNCONFIRMED: member names (buf/sel), prototypes.
 */
typedef unsigned long u_long;
#define VIF0CHCR (*(volatile unsigned int *)0x10009000)
#define GIFCHCR (*(volatile unsigned int *)0x1000A000)
#define GIFMADR (*(volatile unsigned int *)0x1000A010)
#define GIFQWC (*(volatile unsigned int *)0x1000A020)
#define DSTAT (*(volatile unsigned int *)0x10003C00)
#define DPCR (*(volatile unsigned int *)0x10003020)

struct DcEnt {
    unsigned int pad00;
    unsigned int pad04;
    unsigned int flag;
    unsigned int pad0C[11];
};

struct DcCtx {
    struct DcEnt ent[2];        /* 0x00 */
    unsigned int pad70[6];      /* 0x70 */
    unsigned int buf;           /* 0x88 */
    unsigned int pad8C[5];      /* 0x8C */
    volatile unsigned int sel;  /* 0xA0 */
};

extern struct DcCtx D_kernel_bss_1F010;
extern void FlushCache(int mode);
void func_014BA0(void);
int iosDlGetWorkBufId(void);

void iosGsSetDrawContext(void) {
    unsigned int vu0;
    unsigned int f;
    unsigned int pkt;
    long qwc;
    u_long addr;
    u_long addr64;
    int i;
    int id;
    struct DcEnt *e;
    unsigned int m0;
    unsigned int m21;
    struct DcCtx *ctx;

    ctx = &D_kernel_bss_1F010;
    m0 = ~1;
    m21 = ~0x20;
    for (e = (struct DcEnt *)((char *)ctx + 0x10), i = 1; i >= 0; i--) {
        f = e->flag;
        f = (f & m0) | (ctx->sel & 1);
        e->flag = f;
        f = (f & m21) | ((ctx->sel & 1) << 5);
        e->flag = f;
        e++;
    }
    func_014BA0();
    pkt = D_kernel_bss_1F010.buf;
    id = iosDlGetWorkBufId();
    if (id == 0) {
        pkt += 0x190;
    }
    pkt += 0x10;
    addr64 = pkt;
    qwc = (int)(*(unsigned long *)pkt & 0x7FFF) + 1;
    while (1) {
        __asm__ volatile("cfc2.ni %0, $vi29" : "=r"(vu0));
        if (VIF0CHCR & 0x100)
            continue;
        if (GIFCHCR & 0x100)
            continue;
        if (DSTAT & 0x1F000003)
            continue;
        if (vu0 & 0x100)
            continue;
        if (DPCR & 0xC00)
            continue;
        break;
    }
    addr = addr64 & 0xFFFFFFF;
    GIFQWC = qwc;
    GIFMADR = addr;
    FlushCache(0);
    GIFCHCR = 0x141;
}
