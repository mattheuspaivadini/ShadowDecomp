/* asm/cod/021C20.s -> _sceMcCoreWriteSameData.
 * libmc2 core RPC: send command 0xB with (a1, a2) and the card words; returns a2 on success.
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
int sceDbcSendData3(int sock, int slot, int *size, void *data, void (*end)(void *));
void func_00121058(void *arg);
struct McCoreState *func_00120F30(void);

int _sceMcCoreWriteSameData(int port, int a1, int a2) {
    int size;

    if (sceDbcGetConnection(D_00163CC8[port].sock) == 3)
        return 0;
    D_00163D40.f00 = a1;
    D_00163D40.f08 = D_00163CC8[port].f08;
    D_00163D40.f0C = D_00163CC8[port].f0C;
    D_00163D40.f10 = D_00163CC8[port].f10;
    size = 0x2080;
    D_00163D40.f04 = a2;
    D_00163D40.f14 = 0;
    D_00163D40.f18 = 0;
    D_00163D40.f1C = 0;
    D_00163D40.f20 = 0;
    D_00163D40.f24 = D_00163CC8[port].f14;
    func_001283D0(D_00165DC0, 0, 0x100);
    D_00135944 = 0xB;
    while (sceDbcSendData3(D_00163CC8[port].sock, D_00135944, &size, &D_00163D40, func_00121058) != 1)
        ;
    if (func_00120F30()->f08 == 0)
        return 0;
    return a2;
}
