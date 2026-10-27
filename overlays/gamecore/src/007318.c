/* GAMECORE.XFF @ 0x007318 (28 B) - DebugDispTargetStatusForce
 * Evidence: frame 0x10, `jal GetCharacterClass` with `$a0 = $a1` in the delay
 * slot, then `jr $ra` + frame release: the second argument is forwarded and the
 * first is unused. The call is NOT a sibling call, unlike the neighbouring
 * wrappers, so this translation unit is built with
 * `-fno-optimize-sibling-calls` (see c_sources.txt).
 */
int GetCharacterClass(int obj);

void DebugDispTargetStatusForce(int unused, int obj) {
    GetCharacterClass(obj);
}
