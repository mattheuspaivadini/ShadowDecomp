/* asm/cod/00F2D8.s -> func_00106C90.
 * R4 w25a_1
 * MATCHED (Session 8). */
void SetVTLBRefillHandler(unsigned int a0, int *a1);
void SetVCommonHandler(unsigned int a0, int *a1);

extern int _kDebugHandler[];
extern int _kDebugException[];

unsigned int SetDebugHandler(unsigned int idx, int val) {
    unsigned int i;
    int old;

    i = idx - 1;
    if (i >= 0xD)
        return 0xFFFFFFFFu;
    old = _kDebugHandler[idx];
    _kDebugHandler[idx] = val;
    if (i < 3)
        SetVTLBRefillHandler(idx, _kDebugException);
    else
        SetVCommonHandler(idx, _kDebugException);
    return old;
}
