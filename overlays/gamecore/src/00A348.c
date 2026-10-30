/* GAMECORE.XFF @ 0x00A348 (52 B) - GAMEUTIL_constructor_position_filter
 * Evidence: `$a1 = &ZeroPoint`, `jal .text+0xA380` with `$s0 = $a0` in the
 * delay slot, then `$a0 = $s0`, `$f12 = 0.0f` and a sibling `j` to
 * `.text+0xA3A0`.
 * UNCONFIRMED: the callee prototypes (both targets are unnamed statics).
 
 */
extern float ZeroPoint[];
void func_00A380(void *arg, void *zero);
void func_00A3A0(void *arg, float zero);

void GAMEUTIL_constructor_position_filter(void *arg) {
    func_00A380(arg, ZeroPoint);
    func_00A3A0(arg, 0.0f);
}
