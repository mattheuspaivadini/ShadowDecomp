/* asm/cod/01C138.s -> _sceMcFatInit.
 * _sceMcFatInit; indexed for + builtin 2-byte copy (Session 23)
 * MATCHED. */
struct F { char pad00[0x800]; int f800; int f804; char path[0x80]; int f888; int f88C; int f890; int f894; };
extern struct F D_0015DF48[];
extern char D_00138D08[];   /* "/" in .rodata */
/* UNCONFIRMED: the 2-byte lb/sb copy is most likely strcpy(path, "/") expanded
 * as a builtin; written as __builtin_memcpy because a C object may not emit
 * its own .rodata literal. */
int _sceMcFatInit(void) {
    int i;
    for (i = 0; i < 2; i++) {
        D_0015DF48[i].f800 = -1;
        D_0015DF48[i].f804 = -1;
        D_0015DF48[i].f894 = 0;
        D_0015DF48[i].f888 = 1;
        D_0015DF48[i].f88C = 0;
        D_0015DF48[i].f890 = 0;
        __builtin_memcpy(D_0015DF48[i].path, D_00138D08, 2);
    }
    return 1;
}
