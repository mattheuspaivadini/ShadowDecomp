/* STATUS (Session 34, 2026-10-19): NON_MATCHING. best score 159 [cc=29].
 * sceSifInitCmd. Structure follows the asm (handler table, sregs clear, DMAC/SIF setup, two SendCmd
 * paths). Not tuned: frame gets an extra s-reg and the address/constant registers differ.
 * Only the first draft was scored.
 * The original .s stays in the build (asm/cod/012918.s); this C
 * draft (Session 34) is kept for the record. */
struct SifCmdHandler {
    void (*func)(void *, void *);
    void *data;
    int pad;
};

struct SifCmdData {
    void *pktbuf;                       /* 0x00 uncached packet buffer */
    void *unf;                          /* 0x04 */
    void *iopbuf;                       /* 0x08 */
    struct SifCmdHandler *sys_handlers; /* 0x0C */
    int nr_sys;                         /* 0x10 */
    void *usr_handlers;                 /* 0x14 */
    int nr_usr;                         /* 0x18 */
    int *sregs;                         /* 0x1C */
};

struct SifCmdHdr {
    int psize;                          /* 0x00 */
    int dest;                           /* 0x04 */
    int fid;                            /* 0x08 */
    int opt;                            /* 0x0C */
    void *buf;                          /* 0x10 */
};

extern int D_00133948 __attribute__((section(".data")));
extern char D_0014B280[];
extern char D_0014B300[];
extern struct SifCmdHdr D_0014B340;
extern int D_0014B354[];
extern struct SifCmdData D_0014B358;
extern struct SifCmdHandler D_0014B380[0x20];
extern int D_0014B500[0x20];

int DIntr(void);
int EIntr(void);
void FlushCache(int mode);
void sceSifSetDChain(void);
int AddDmacHandler(int ch, int (*fn)(int), int next);
int EnableDmac(int ch);
unsigned int sceSifGetReg(unsigned int reg);
int sceSifSetReg(unsigned int reg, unsigned int val);
int sceSifSendCmd(int id, void *pkt, int size, void *src, void *dst, int n);
void func_001128C0(void *, void *);
void func_001128A0(void *, void *);
int func_00112E80(int ch);

#define UNCACHED(p) ((void *)((unsigned int)(p) | 0x20000000))
#define D_STAT ((volatile unsigned int *)0x1000E010)
#define D_CTRL ((volatile unsigned int *)0x1000C000)

void sceSifInitCmd(void) {
    struct SifCmdHandler *h;
    int i;

    DIntr();
    if (D_00133948 != 0) {
        EIntr();
        return;
    }
    D_00133948 = 1;
    D_0014B358.pktbuf = UNCACHED(D_0014B280);
    D_0014B358.sregs = D_0014B500;
    D_0014B358.unf = UNCACHED(D_0014B300);
    D_0014B358.nr_sys = 0x20;
    D_0014B358.iopbuf = 0;
    D_0014B358.sys_handlers = D_0014B380;
    D_0014B358.usr_handlers = 0;
    D_0014B358.nr_usr = 0;
    for (h = D_0014B380; h < D_0014B380 + 0x20; h++) {
        h->func = 0;
        h->data = 0;
    }
    for (i = 31; i >= 0; i--)
        D_0014B500[i] = 0;
    D_0014B380[0].func = func_001128C0;
    D_0014B380[1].func = func_001128A0;
    D_0014B380[1].data = &D_0014B358;
    D_0014B380[0].data = &D_0014B358;
    EIntr();
    FlushCache(0);
    if (*D_STAT & 0x20)
        *D_STAT = 0x20;
    if (!(*D_CTRL & 0x100))
        sceSifSetDChain();
    D_0014B354[0] = AddDmacHandler(5, func_00112E80, 0);
    EnableDmac(5);
    D_0014B358.iopbuf = (void *)sceSifGetReg(0x80000000);
    if (D_0014B358.iopbuf != 0) {
        D_0014B340.buf = D_0014B280;
        sceSifSendCmd(0x80000000, &D_0014B340, 0x14, 0, 0, 0);
        return;
    }
    while (!(sceSifGetReg(4) & 0x20000))
        ;
    D_0014B358.iopbuf = (void *)sceSifGetReg(2);
    sceSifSetReg(0x80000000, (unsigned int)D_0014B358.iopbuf);
    sceSifSetReg(0x80000001, (unsigned int)&D_0014B358);
    D_0014B340.buf = D_0014B280;
    D_0014B340.opt = 0;
    sceSifSendCmd(0x80000002, &D_0014B340, 0x14, 0, 0, 0);
}
