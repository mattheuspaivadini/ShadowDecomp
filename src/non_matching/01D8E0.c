/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 10 [cc=29].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/01D8E0.s); this C
 * draft (Session 9) is kept for the record. */
int _sceMcCoreGetConnection(int a0);
int _sceMcpCheckNewCard(int a0);
int _sceMcpAuthentication(int a0);
int _sceMcCoreWriteBack(int a0);
extern char D_0015DF48[];

int func_0011D8E0(int a0) {
    int id = a0;
    char *p;
    int r;

    if (_sceMcCoreGetConnection(a0) == 0)
        return 0x81010013;
    if (_sceMcpCheckNewCard(id) == 0)
        return 0x81019003;
    p = D_0015DF48 + 0x898 * id;
    r = *(int *)(p + 0x888);
    if (r == 1)
        return 0x81019003;
    if (*(int *)(p + 0x88C) != 0)
        return 0x8101002F;
    if (_sceMcpAuthentication(id) == 0)
        return 0x81010013;
    _sceMcCoreWriteBack(id);
    return 0;
}
