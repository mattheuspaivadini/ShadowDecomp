/* GAMECORE.XFF @ 0x015460 (36 B) - setGameHardMode
 * Evidence: `$a0 -> $v0`, `sltu $a0, $zero, $v0` (mode != 0) and an `sw` of
 * the argument to .bss+0xC7C, then a sibling `j` to
 * `SetDamageClassDamageTableType` with that boolean.
 * UNCONFIRMED: the .bss field meaning and the callee prototype.
 
 */
extern int D_kernel_bss_0C7C[];
void SetDamageClassDamageTableType(int hard);

void setGameHardMode(int mode) {
    D_kernel_bss_0C7C[0] = mode;
    SetDamageClassDamageTableType(mode != 0);
}
