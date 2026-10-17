/* asm/cod/021A70.s -> _sceMcCoreReadPage.
 * libmc2 _sceMcCoreReadPage (matching, cc=29)
 * MATCHED. */
struct R021A70 {
    char pad00[0x14];
    int  field14;             /* 0x14 */
    char rest[0x24 - 0x18];   /* stride 0x24 */
};

extern struct R021A70 D_00163CC8[];

void _sceMcCoreReadPage2(int a0, int a1, int a2, int a3, int a4);

void _sceMcCoreReadPage(int a0, int a1, int a2, int a3) {
    _sceMcCoreReadPage2(a0, a1, a2, a3, D_00163CC8[a0].field14);
}
