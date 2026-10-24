/* MANAGER.XFF @ 0x0EE628 - static function (no symbol in the shipped .symtab).
 * Recovered mechanically by tools/xff_autotry.py: the body is a frame whose only
 * work is a single tail call, and the reconstruction compiles byte-exactly with the
 * relocations masked (tools/xffcheck.py).
 * UNCONFIRMED: the arity of the callee (no argument registers are set, so the
 * incoming registers are forwarded untouched) and the name (Ghidra's FUN_002EE628
 * for this range).
 */
void func_0EE628(void) {
    isysRequestDeleteObj();
}
