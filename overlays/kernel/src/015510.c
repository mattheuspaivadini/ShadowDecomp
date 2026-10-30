/* KERNEL.XFF @ 0x015510 (364 B) - iosSetScreenEnv
 * Evidence: the four .data+0x5B0 state words (0x5B8 = 0, 0x5B4 = 0x5B8,
 * 0x5B0 = 0x5B4, 0x5BC = 0x80, each read back: the objects are volatile); the
 * five-poll DMA/VU0 wait of iosDmaSendPath1; waitVscheduler(); an unused read of
 * the GS CSR (0x12001000); iosGsSetMode(); the inlined iosResetGraph(0,
 * .data+0x5A0, +0x5A4, +0x5A8) (CSR = 0x200 then sceGsResetGraph); func_014910();
 * func_014CF8(); the two-entry .bss+0x1F010 bit-0/bit-5 copy loop (entries at
 * base+0x10, stride 0x38, flag word at +8, source bit base+0xA0) and a tail call
 * to func_014BA0. The two flag masks are locals assigned before the loop, which
 * is what puts their `li` in front of the loop-init in the preheader.
 * UNCONFIRMED: names, the state-word layout.
 */
#define VIF0CHCR (*(volatile unsigned int *)0x10009000)
#define GIFCHCR (*(volatile unsigned int *)0x1000A000)
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

extern volatile unsigned int D_kernel_data_05B0[4];
extern short D_kernel_data_05A0;
extern short D_kernel_data_05A4;
extern short D_kernel_data_05A8;
extern struct DcCtx D_kernel_bss_1F010;
void waitVscheduler(void);
void iosGsSetMode(void);
void sceGsResetGraph(short mode, short inter, short omode, short ffmode);
void func_014910(void);
void func_014CF8(void);
void func_014BA0(void);

static inline void iosResetGraph(short mode, short inter, short omode, short ffmode) {
    if (mode != 0) {
        *(volatile unsigned long *)0x12001000 = 0x100;
        return;
    }
    *(volatile unsigned long *)0x12001000 = 0x200;
    sceGsResetGraph(0, inter & 1, omode, ffmode & 1);
}

void iosSetScreenEnv(void) {
    unsigned int vu0;
    struct DcEnt *e;
    struct DcCtx *ctx;
    unsigned int f;
    unsigned int m0;
    unsigned int m21;
    int i;

    D_kernel_data_05B0[2] = 0;
    D_kernel_data_05B0[1] = D_kernel_data_05B0[2];
    D_kernel_data_05B0[0] = D_kernel_data_05B0[1];
    D_kernel_data_05B0[3] = 0x80;
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
    waitVscheduler();
    *(volatile unsigned long *)0x12001000;
    iosGsSetMode();
    iosResetGraph(0, D_kernel_data_05A0, D_kernel_data_05A4, D_kernel_data_05A8);
    func_014910();
    func_014CF8();
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
}
