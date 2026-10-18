/* asm/cod/01D7E0.s -> _sceMcFatUnFormat.
 * _sceMcFatUnFormat; per-statement FAT record indexing, _sceMcCoreGetConnection(port) arity, card-spec struct (Session 23)
 * MATCHED. */
struct F { char pad00[0x800]; int f800; int f804; char path[0x80]; int f888; int f88C; int f890; int f894; };
struct CardSpec { int f00; int blocksize; int cardsize; int f0C; };
extern struct F D_0015DF48[];
extern char D_00138D08[];   /* "/" in .rodata */
int _sceMcCoreGetConnection(int port);
int _sceMcpGetCardSpec(int port, struct CardSpec *spec);
int _sceMcCoreBlockErase(int port, int block);

/* UNCONFIRMED: the 2-byte lb/sb copy is most likely strcpy(path, "/") expanded
 * as a builtin; written as __builtin_memcpy because a C object may not emit
 * its own .rodata literal. */
int _sceMcFatUnFormat(int port) {
    struct CardSpec spec;
    int n;
    int i;

    if (_sceMcCoreGetConnection(port) == 0)
        return 0x81010013;
    if (_sceMcpGetCardSpec(port, &spec) == 0)
        return 0x8101006F;
    D_0015DF48[port].f894 = 0;
    D_0015DF48[port].f800 = -1;
    D_0015DF48[port].f804 = -1;
    D_0015DF48[port].f890 = 0;
    D_0015DF48[port].f88C = 0;
    __builtin_memcpy(D_0015DF48[port].path, D_00138D08, 2);
    n = spec.cardsize / spec.blocksize;
    for (i = 0; i < n; i++)
        if (_sceMcCoreBlockErase(port, i) == 0)
            return 0x8101006F;
    return 0;
}
