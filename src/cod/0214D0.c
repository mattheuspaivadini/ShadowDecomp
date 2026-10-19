/* asm/cod/0214D0.s -> _sceMcCoreClearNewCardFlag.
 * libmc2 core RPC: send command 0xD with an empty card block.
 * MATCHED. */
/* asm/cod/0213D0.s -> _sceMcCoreCheckNewCard.
 * libmc2 core RPC: copy the record's 3 card words into the command block, send command 4. */
struct McCoreRec {
    int  field00;
    int  sock;                  /* 0x04 */
    int  f08;                   /* 0x08 */
    int  f0C;                   /* 0x0C */
    int  f10;                   /* 0x10 */
    char rest[0x24 - 0x14];     /* stride 0x24 */
};

struct McCoreCmd {
    char pad00[8];
    int  f08;                   /* 0x08 */
    int  f0C;                   /* 0x0C */
    int  f10;                   /* 0x10 */
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
int sceDbcSendData3(int sock, int slot, int *size, void *data, void (*end)(void *));
void func_00121058(void *arg);
struct McCoreState *func_00120F30(void);

int _sceMcCoreClearNewCardFlag(int port) {
    int size;
    
    if (sceDbcGetConnection(D_00163CC8[port].sock) == 3)
        return 0;
    D_00163D40.f14 = 0;
    D_00163D40.f18 = 0;
    size = 0x2080;
    func_001283D0(D_00165DC0, 0, 0x100);
    D_00135944 = 0xD;
    while (sceDbcSendData3(D_00163CC8[port].sock, D_00135944, &size, &D_00163D40, func_00121058) != 1)
        ;
    return func_00120F30()->f08;
}
