/* GAMECORE.XFF @ 0x0078C0 (48 B) - ResetObject
 * Evidence: `$a0` saved in `$s0`, `jal ForceUnparentLayoutObj` with the original
 * `$a0`, `jal CallLayoutObjDebugResetFunc` with `$a0 = $s0`, then a sibling `j`
 * (tail call) to `.text+0` with `$a0 = $s0`.
 * UNCONFIRMED: the callee at `.text+0` has no symbol in the module table.
 
 */
void ForceUnparentLayoutObj(void *obj);
void CallLayoutObjDebugResetFunc(void *obj);
void func_000000(void *obj);

void ResetObject(void *obj) {
    ForceUnparentLayoutObj(obj);
    CallLayoutObjDebugResetFunc(obj);
    func_000000(obj);
}
