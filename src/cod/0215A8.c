/* asm/cod/0215A8.s -> _sceMcCoreAuthentication.
 * libmc2 core RPC: send command 0xC; index D_00163CC8[port] per statement (a sock
 * pointer local folds the +4 into %lo, the Session 28 blocker).
 * MATCHED. */
struct McCoreRec {
    int  field00;
    int  sock;                  /* 0x04 */
    char rest[0x24 - 8];        /* stride 0x24 */
};

struct McCoreCmd {
    char pad00[0x14];
    int  f14;                   /* 0x14 */
    int  f18;                   /* 0x18 */
};

struct McCoreState {
    char pad00[8];
    int  f08;                   /* 0x08 */
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

int _sceMcCoreAuthentication(int port) {
    int size;

    if (sceDbcGetConnection(D_00163CC8[port].sock) == 3)
        return 0;
    D_00163D40.f14 = 0;
    D_00163D40.f18 = 0;
    size = 0x2080;
    func_001283D0(D_00165DC0, 0, 0x100);
    SyncDCache(D_00165DC0, D_00165DC0 + 0xFF);
    D_00135944 = 0xC;
    while (sceDbcSendData3(D_00163CC8[port].sock, D_00135944, &size, &D_00163D40, func_00121058) != 1)
        ;
    return func_00120F30()->f08 != 0;
}
