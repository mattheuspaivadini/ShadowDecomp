/* GAMECORE.XFF @ 0x07B8C0 (56 B) - playerWeaponChangeIconMax
 * Evidence: `lui/addiu $a0 = gcGlobalVar+0x2B0`, `jal SCRGetFirstObj`, the
 * result null-tested and passed on in `$a0` to `GetSCRCharaAIWorkPtr`, then
 * `$v1 = 1` stored at +0x80.
 * UNCONFIRMED: the `gcGlobalVar` field and the AI work field meanings.
 
 */
struct GcGlobal {
    char pad[0x2B0];
    int field2B0;
};

struct SCRCharaAIWork {
    char pad[0x80];
    int f80;
};

extern struct GcGlobal gcGlobalVar;
void *SCRGetFirstObj(void *param);
struct SCRCharaAIWork *GetSCRCharaAIWorkPtr(void *obj);

void playerWeaponChangeIconMax(void) {
    void *obj = SCRGetFirstObj(&gcGlobalVar.field2B0);

    if (obj != 0)
        GetSCRCharaAIWorkPtr(obj)->f80 = 1;
}
