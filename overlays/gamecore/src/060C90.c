/* GAMECORE.XFF @ 0x060C90 (52 B) - MotSpdCtrl_Init
 * Evidence: `$a0`/`$a1` saved in `$s0`/`$s1`, `jal .text+0x60DA0` with `$a0`
 * untouched, then `sw $s1,0x14($s0)`.
 * UNCONFIRMED: the callee prototype and the field meaning.
 
 */
struct MotSpdCtrl {
    char pad[0x14];
    int f14;
};

void func_060DA0(void *ctrl);

void MotSpdCtrl_Init(struct MotSpdCtrl *ctrl, int param) {
    func_060DA0(ctrl);
    ctrl->f14 = param;
}
