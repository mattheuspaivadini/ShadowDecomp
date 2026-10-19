/* asm/cod/0161A0.s -> sceDbcGetConnection.
 * Session 8 draft (never promoted), byte-exact at cc=29: SyncDCache + DIntr/EIntr-guarded 0x40-byte struct copy, same idiom as 016030 (Session 28).
 * MATCHED. */
struct DbcConnBuf {
    int words[16];
};

extern struct DbcConnBuf D_00150D00;
extern struct DbcConnBuf D_00150D80;

void SyncDCache(void *start, void *end);
int DIntr(void);
int EIntr(void);

int sceDbcGetConnection(int idx) {
    SyncDCache(&D_00150D00, (char *)&D_00150D00 + 0x80);
    DIntr();
    D_00150D80 = D_00150D00;
    EIntr();
    return (D_00150D80.words[idx] == 1) ? 1 : 3;
}
