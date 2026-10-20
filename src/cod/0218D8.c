/* asm/cod/0218D8.s -> _sceMcCoreReadPage2.
 * libmc2 core RPC: send the read command, then copy `count` pages out of the per-port cache.
 * MATCHED. */
struct McCoreRec {
    int  field00;
    int  sock;                  /* 0x04 */
    int  f08;                   /* 0x08 */
    int  f0C;                   /* 0x0C */
    int  f10;                   /* 0x10 */
    int  f14;                   /* 0x14 */
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
    unsigned char data[0x2000]; /* 0x28 */
};

struct McCoreState {
    char pad00[8];
    int  f08;                   /* 0x08 */
};

extern struct McCoreRec D_00163CC8[];
extern struct McCoreCmd D_00163D40;
extern unsigned char D_00165DC0[];
extern int D_00135944 __attribute__((section(".data")));
extern unsigned char D_00165E40[];

int sceDbcGetConnection(int sock);
void *func_0012821C(void *dst, const void *src, unsigned int size);  /* memcpy */
void *func_001283D0(void *dst, int c, unsigned int size);   /* memset */
void SyncDCache(void *start, void *end);
int sceDbcSendData3(int sock, int slot, int *size, void *data, void (*end)(void *));
void func_00121058(void *arg);
struct McCoreState *func_00121000(void);

int _sceMcCoreReadPage2(int port, unsigned char *buf, int page, int count, int a4) {
    int size;
    unsigned char *p;
    unsigned char *dst;
    int i;

    if (sceDbcGetConnection(D_00163CC8[port].sock) == 3)
        return 0;
    D_00163D40.f24 = a4;
    D_00163D40.f00 = page;
    D_00163D40.f08 = D_00163CC8[port].f08;
    D_00163D40.f0C = D_00163CC8[port].f0C;
    D_00163D40.f10 = D_00163CC8[port].f10;
    size = 0x2080;
    D_00163D40.f14 = 0;
    D_00163D40.f18 = 0;
    D_00163D40.f1C = 0;
    D_00163D40.f20 = 0;
    D_00163D40.f04 = count;
    func_001283D0(D_00165DC0, 0, 0x100);
    D_00135944 = 1;
    while (sceDbcSendData3(D_00163CC8[port].sock, D_00135944, &size, &D_00163D40, func_00121058) != 1)
        ;
    if (func_00121000()->f08 == 0)
        return 0;
    dst = buf;
    p = D_00165E40;
    for (i = 0; i < count; i++) {
        SyncDCache(p, p + D_00163D40.f08);
        func_0012821C(dst, p, D_00163D40.f08);
        p += D_00163D40.f08;
        dst += D_00163D40.f08;
    }
    return count;
}
