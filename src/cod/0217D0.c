/* asm/cod/0217D0.s -> _sceMcCoreReadClock.
 * libmc2 core RPC: send command 0xA, copy the 8-byte clock out on success.
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

struct McClock {                /* 8 bytes, byte-aligned (ldl/ldr copy) */
    unsigned char b[8];
};

struct McCoreState {
    char pad00[8];
    int  f08;                   /* 0x08 */
    struct McClock clock;       /* 0x0C */
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

int _sceMcCoreReadClock(int port, struct McClock *clock) {
    struct McCoreState *st;
    int size;
    
    if (sceDbcGetConnection(D_00163CC8[port].sock) == 3)
        return 0;
    D_00163D40.f14 = 0;
    D_00163D40.f18 = 0;
    size = 0x2080;
    func_001283D0(D_00165DC0, 0, 0x100);
    D_00135944 = 0xA;
    while (sceDbcSendData3(D_00163CC8[port].sock, D_00135944, &size, &D_00163D40, func_00121058) != 1)
        ;
    st = func_00120F30();
    if (st->f08 == 0)
        return 0;
    *clock = st->clock;
    return st->f08;
}
