/* asm/cod/0211F8.s -> _sceMcCoreGetCardSpec.
 * libmc2 core RPC command 3: decode the little-endian spec bytes of the reply into the record block and copy it out; f24 = 0 written after the other zero fields (Session 34)
 * MATCHED. */
struct B0211B8 {                /* 16-byte block stored at record + 0x08 */
    unsigned int w0;            /* 0x00 */
    unsigned int w4;            /* 0x04 */
    unsigned int w8;            /* 0x08 */
    unsigned int wC;            /* 0x0C */
};

struct McCoreRec {
    int  field00;
    int  sock;                  /* 0x04 */
    struct B0211B8 blk;         /* 0x08 */
    int  f18;                   /* 0x18 */
    int  f1C;                   /* 0x1C */
    int  f20;                   /* 0x20 */
};

struct McCoreCmd {
    int  f00;                   /* 0x00 */
    int  f04;                   /* 0x04 */
    int  f08;                   /* 0x08 */
    int  f0C;                   /* 0x0C */
    int  f10;                   /* 0x10 */
    int  f14;                   /* 0x14 */
    int  f18;                   /* 0x18 */
    int  f1C;                   /* 0x1C */
    int  f20;                   /* 0x20 */
    int  f24;                   /* 0x24 */
};

struct McCoreState {
    char pad00[8];
    int  f08;                   /* 0x08 */
    unsigned char b[0x10];      /* 0x0C */
};

extern struct McCoreRec D_00163CC8[];
extern struct McCoreCmd D_00163D40;
extern unsigned char D_00165DC0[];
extern int D_00135944 __attribute__((section(".data")));

int sceDbcGetConnection(int sock);
void *func_001283D0(void *dst, int c, unsigned int size);   /* memset */
void SyncDCache(void *start, void *end);
int sceDbcSendData3(int sock, int slot, int *size, void *data, void (*end)(void *));
void func_00121058(void *arg);
struct McCoreState *func_00120F30(void);

int _sceMcCoreGetCardSpec(int port, struct B0211B8 *spec) {
    int size;
    struct McCoreState *st;

    if (sceDbcGetConnection(D_00163CC8[port].sock) == 3)
        return 0;
    size = 0x2080;
    D_00163D40.f08 = 0;
    D_00163D40.f0C = 0;
    D_00163D40.f10 = 0;
    D_00163D40.f14 = 0;
    D_00163D40.f18 = 0;
    D_00163D40.f1C = 0;
    D_00163D40.f20 = 0;
    D_00163D40.f24 = 0;
    func_001283D0(D_00165DC0, 0, 0x100);
    SyncDCache(D_00165DC0, D_00165DC0 + 0xFF);
    D_00135944 = 3;
    while (sceDbcSendData3(D_00163CC8[port].sock, D_00135944, &size, &D_00163D40, func_00121058) != 1)
        ;
    st = func_00120F30();
    if (st->f08 == 0)
        return 0;
    D_00163CC8[port].blk.w0 = st->b[0] + (st->b[1] << 8);
    D_00163CC8[port].blk.w4 = st->b[2] + (st->b[3] << 8);
    D_00163CC8[port].blk.w8 = st->b[4] + (st->b[5] << 8) + (st->b[6] << 16) + (st->b[7] << 24);
    D_00163CC8[port].blk.wC = 1;
    *spec = D_00163CC8[port].blk;
    return 1;
}
