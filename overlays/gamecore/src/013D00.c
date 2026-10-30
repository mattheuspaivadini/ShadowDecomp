/* GAMECORE.XFF @ 0x013D00 (48 B) - setFadeParam
 * Evidence: `lwc1 $f2,0x10($a0)` then the global `gcGlobalVar+0x168` is loaded
 * twice (`$f0`, `$f1`), so the source reads the field twice; stores go to
 * +0x0 (global), +0x4 (global + `$f13`), +0x8 (the +0x10 value), +0xC
 * (`$f12`) and +0x14 (`$a1`, a word store).
 * UNCONFIRMED: the struct field meanings and the parameter names.
 
 */
struct GcGlobal {
    char pad[0x168];
    float fade;
};
extern struct GcGlobal gcGlobalVar;

struct FadeParam {
    float cur;
    float next;
    float from;
    float to;
    float time;
    int flag;
};

void setFadeParam(struct FadeParam *p, int flag, float to, float rate) {
    p->cur = gcGlobalVar.fade;
    p->next = gcGlobalVar.fade + rate;
    p->from = p->time;
    p->to = to;
    p->flag = flag;
}
