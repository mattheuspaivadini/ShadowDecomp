/* GAMECORE.XFF @ 0x04FBE0 (40 B) - demo_PlayerDeathEffectStart
 * Evidence: `mtc1` of the constant 0x3CBE60A0 (0.023239434f) into `$f12`,
 * `$a0 = 0x800`, `$a1 = 0x800`, sibling `j` to `setBossDeathEffect`.
 * UNCONFIRMED: the callee prototype and the two 0x800 arguments' meanings.
 
 */
void setBossDeathEffect(int a, int b, float c);

void demo_PlayerDeathEffectStart(void) {
    setBossDeathEffect(0x800, 0x800, 0.023239434f);
}
