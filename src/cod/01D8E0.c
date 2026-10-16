/* asm/cod/01D8E0.s -> func_0011D8E0.
 * func_0011D8E0: D_0015DF48 array indexing with mult 0x898
 * MATCHED (Session 12). */
struct R01D8E0 {
    char pad00[0x888];
    int status;
    int flags;
    char pad890[8];
};
extern struct R01D8E0 D_0015DF48[];

int _sceMcCoreGetConnection(int a0);
int _sceMcpCheckNewCard(int a0);
int _sceMcpAuthentication(int a0);
int _sceMcCoreWriteBack(int a0);

int func_0011D8E0(int a0) {
    if (_sceMcCoreGetConnection(a0) == 0)
        return 0x81010013;
    if (_sceMcpCheckNewCard(a0) == 0)
        return 0x81019003;
    if (D_0015DF48[a0].status == 1)
        return 0x81019003;
    if (D_0015DF48[a0].flags == 0)
        return 0x8101002F;
    if (_sceMcpAuthentication(a0) == 0)
        return 0x81010013;
    _sceMcCoreWriteBack(a0);
    return 0;
}
