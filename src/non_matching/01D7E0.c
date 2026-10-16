/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 38 [cc=29].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/01D7E0.s); this C
 * draft (Session 9) is kept for the record. */
struct R01D7E0 {
    char pad00[0x800];
    int  f800;              /* 0x800 */
    int  f804;              /* 0x804 */
    char f808;              /* 0x808 */
    char f809;              /* 0x809 */
    char pad80A[0x82];
    int  f88C;              /* 0x88C */
    int  f890;              /* 0x890 */
    int  f894;              /* 0x894 */
};

extern struct R01D7E0 D_0015DF48[];

extern char D_00138D08[];
extern int _sceMcCoreGetConnection(void);
extern int _sceMcpGetCardSpec(int a0, int *a1);
extern int _sceMcCoreBlockErase(int a0, int a1);

int _sceMcFatUnFormat(int index) {
    int tmp[4];
    struct R01D7E0 *p;
    int n;
    int i;

    if (_sceMcCoreGetConnection() == 0)
        return 0x81010013;
    if (_sceMcpGetCardSpec(index, tmp) == 0)
        return 0x8101006F;
    p = &D_0015DF48[index];
    p->f894 = 0;
    p->f800 = -1;
    p->f804 = -1;
    p->f890 = 0;
    p->f88C = 0;
    p->f808 = D_00138D08[0];
    p->f809 = D_00138D08[1];
    n = tmp[2] / tmp[1];
    if (n <= 0)
        return 0;
    for (i = 0; i < n; i++) {
        if (_sceMcCoreBlockErase(index, i) == 0)
            return 0x8101006F;
    }
    return 0;
}
