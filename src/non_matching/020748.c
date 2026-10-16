/* STATUS (Session 6, step 3): NON_MATCHING - best attempt [cc=29] is not byte-exact.
 * The corrected struct (0x184 stride, field +0x2A) reproduces the right
 * instructions (addiu 0x184 / mult / lhu 0x2A / two mults) but the
 * register roles differ (original: stride+base in $v1, w in $a4; ours:
 * $t0/$v0/$v1). Score 8 instructions at cc=29 (old-struct variant: 5,
 * coincidental). 10 expression-shape variants tried; all >=5.
 * See docs/non-matching-backlog.md. */
 *
 * Look up the record at `index` (stride 0x184), read the unsigned short at
 * +0x2A and forward _sceMcCoreWritePage(index, a1, a2 * w, a3 * w). Same shape as
 * _sceMcpReadClust (see the note there about the 0x184 stride).
 *
 * MATCHED (Session 6, step 3) with cc=29.
 */
struct R020748 {
    char pad00[0x2A];
    unsigned short w;            /* 0x2A */
    char rest[0x184 - 0x2C];     /* stride 0x184 */
};

extern struct R020748 gSceMc2SysInfo[];

int _sceMcCoreWritePage(int a0, int a1, int a2, int a3);

int _sceMcpWriteClust(int index, int a1, int a2, int a3) {
    unsigned short w = gSceMc2SysInfo[index].w;

    return _sceMcCoreWritePage(index, a1, a2 * w, a3 * w);
}
/* func_00120748 */
