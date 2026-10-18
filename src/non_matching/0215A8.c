/* STATUS (Session 28, 2026-10-18): NON_MATCHING. best score 39 [cc=29].
 * Positional score; an aligned diff leaves ~12 lines. The original materialises &D_00163CC8[port].sock as lui/addiu %lo then a separate addiu +4 (we fold the +4 into %lo), so everything after shifts by one insn; rest = s1/s2 roles of the sock pointer and the D_00135944 base. Tried f[1] array field, rec pointer + &rec->sock, (int *)&rec[port] + 1, base + port * 9: no change.
 * The original .s stays in the build (asm/cod/0215A8.s); this C
 * draft (Session 28) is kept for the record. */
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
    int *sock = &D_00163CC8[port].sock;
    int size;

    if (sceDbcGetConnection(*sock) == 3)
        return 0;
    size = 0x2080;
    D_00163D40.f14 = 0;
    D_00163D40.f18 = 0;
    func_001283D0(D_00165DC0, 0, 0x100);
    SyncDCache(D_00165DC0, D_00165DC0 + 0xFF);
    D_00135944 = 0xC;
    while (sceDbcSendData3(*sock, D_00135944, &size, &D_00163D40, func_00121058) != 1)
        ;
    return func_00120F30()->f08 != 0;
}
