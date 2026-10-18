/* asm/cod/008FF8.s -> sceSifInitRpc.
 * sceSifInitRpc; void prototypes for the tail-called EIntr/sceSifSetReg, typed rpc data-queue record, store order from the permuter (Session 23)
 * MATCHED. */
typedef struct {
    int active;             /* 0x00 */
    void *data;             /* 0x04 uncached rpc packet buffer */
    int size;               /* 0x08 */
    int f0C;                /* 0x0C */
    int f10;                /* 0x10 */
    void *pkt_table;        /* 0x14 */
    int pkt_count;          /* 0x18 */
    void *client_table;     /* 0x1C */
    int client_count;       /* 0x20 */
    void *link;             /* 0x24 */
} SifRpcDataQueue;
extern int D_00132288 __attribute__((section(".data")));
extern int D_00144140[];   /* 0x800 bytes */
extern char D_00144940[];
extern char D_00145140[];
extern SifRpcDataQueue D_00145940;
int DIntr(void);
void EIntr(void);
void sceSifInitCmd(void);
void sceSifAddCmdHandler(int id, void (*fn)(void), void *arg);
int sceSifGetReg(int id);
int sceSifSendCmd(int id, void *pkt, int size, void *src, void *dst, int n);
int sceSifGetSreg(int n);
void sceSifSetReg(int id, int val);
void func_001092F8(void);
void func_001096D0(void);
void func_001098F0(void);
void func_00109408(void);
#define UNCACHED(p) ((void *)((unsigned int)(p) | 0x20000000))

void sceSifInitRpc(void) {
    int r;
    int *p;

    DIntr();
    if (D_00132288) {
        EIntr();
        return;
    }
    D_00132288 = 1;
    EIntr();
    sceSifInitCmd();
    DIntr();
    D_00145940.data = UNCACHED(D_00144140);
    D_00145940.size = 0x20;
    D_00145940.f0C = 0;
    D_00145940.pkt_table = UNCACHED(D_00144940);
    D_00145940.f10 = 0;
    D_00145940.pkt_count = 0x20;
    D_00145940.client_table = UNCACHED(D_00145140);
    D_00145940.link = 0;
    D_00145940.client_count = 0x20;
    D_00145940.active = 1;
    sceSifAddCmdHandler(0x80000008, func_001092F8, &D_00145940);
    sceSifAddCmdHandler(0x80000009, func_001096D0, &D_00145940);
    sceSifAddCmdHandler(0x8000000A, func_001098F0, &D_00145940);
    sceSifAddCmdHandler(0x8000000C, func_00109408, &D_00145940);
    EIntr();
    r = sceSifGetReg(0x80000002);
    if (r != 0)
        return;
    p = D_00144140 + 0x10;
    p[3] = 1;
    sceSifSendCmd(0x80000002, p, 0x10, 0, 0, 0);
    while (sceSifGetSreg(0) == 0)
        ;
    sceSifSetReg(0x80000002, 1);
}
