/* asm/cod/021A90.s -> _sceMcCoreWritePage.
 * libmc2 core RPC: copy count pages into the command buffer (cap 0x2000), clear+flush the reply area, send command 2 (Session 34)
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
extern char D_00138D90[];

int sceDbcGetConnection(int sock);
void *func_0012821C(void *dst, const void *src, unsigned int size);  /* memcpy */
void *func_001283D0(void *dst, int c, unsigned int size);   /* memset */
void SyncDCache(void *start, void *end);
int scePrintf(const char *fmt, ...);
int sceDbcSendData3(int sock, int slot, int *size, void *data, void (*end)(void *));
void func_00121058(void *arg);
struct McCoreState *func_00120F30(void);

int _sceMcCoreWritePage(int port, void *buf, int page, int count) {
    int size;
    unsigned int len;

    if (sceDbcGetConnection(D_00163CC8[port].sock) == 3)
        return 0;
    len = D_00163CC8[port].f08 * count;
    if (len > 0x2000) {
        scePrintf(D_00138D90);
        return 0;
    }
    D_00163D40.f00 = page;
    D_00163D40.f08 = D_00163CC8[port].f08;
    D_00163D40.f0C = D_00163CC8[port].f0C;
    D_00163D40.f10 = D_00163CC8[port].f10;
    D_00163D40.f14 = D_00163CC8[port].f20;
    D_00163D40.f18 = D_00163CC8[port].f1C;
    D_00163D40.f24 = D_00163CC8[port].f14;
    D_00163D40.f04 = count;
    D_00163D40.f1C = 0;
    D_00163D40.f20 = 0;
    func_0012821C(D_00163D40.data, buf, len);
    size = 0x2080;
    func_001283D0(D_00165DC0, 0, 0x100);
    SyncDCache(D_00165DC0, D_00165DC0 + 0xFF);
    D_00135944 = 2;
    while (sceDbcSendData3(D_00163CC8[port].sock, D_00135944, &size, &D_00163D40, func_00121058) != 1)
        ;
    if (func_00120F30()->f08 == 0)
        return 0;
    return count;
}
