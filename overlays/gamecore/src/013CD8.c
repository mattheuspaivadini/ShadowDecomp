/* GAMECORE.XFF @ 0x013CD8 (40 B) - initFadeParam
 * Evidence: lui/addiu gcGlobalVar, two separate `lwc1 0x168` loads (fade),
 * `swc1` to +0x0 and +0x4; then three `swc1 $f12` (rate) to +0xC, +0x8 and
 * (delay slot of `jr`) +0x10.
 * UNCONFIRMED: the struct/array meaning; store order is the scheduler's.
 */
struct GcGlobal {
    char pad[0x168];
    float fade;
};
extern struct GcGlobal gcGlobalVar;

void initFadeParam(float *param, float rate) {
    param[0] = gcGlobalVar.fade;
    param[1] = gcGlobalVar.fade;
    param[2] = rate;
    param[4] = rate;
    param[3] = rate;
}
