/* KERNEL.XFF @ 0x009978 (152 B) - isysResolveOneModuleObj
 * Evidence: iosResetCpuRapCounter(2); r = static .text+0x7DC8 (obj); iosGetCpuRapCountPar1Int(); a relocated object (flag 0x20000000 in +0x2C) is re-linked by the static .text+0x77D8 (obj, 0) only when r is set, otherwise it is linked with (obj, 1) and flagged; iosGetCpuRapCountPar1Int(); returns r. UNCONFIRMED: callee names.
 */
struct XffObj {
    char pad[0x2C];
    unsigned int flags;
};
void iosResetCpuRapCounter(int mode);
float iosGetCpuRapCountPar1Int(void);
int func_007DC8(struct XffObj *obj);
void func_0077D8(struct XffObj *obj, int first);

int isysResolveOneModuleObj(struct XffObj *obj) {
    int r;

    iosResetCpuRapCounter(2);
    r = func_007DC8(obj);
    iosGetCpuRapCountPar1Int();
    if (obj->flags & 0x20000000) {
        if (r) {
            func_0077D8(obj, 0);
        }
    } else {
        func_0077D8(obj, 1);
        obj->flags |= 0x20000000;
    }
    iosGetCpuRapCountPar1Int();
    return r;
}
