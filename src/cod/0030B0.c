/* asm/cod/0030B0.s -> func_001030B0 @ 0x001030B0
 * Tail-call trampoline to func_0010C230 (frame + `j`, the cc=296 shape -
 * same family as the matched func_00103008). Parameter count UNCONFIRMED
 * (pure pass-through; the emitted bytes do not depend on it). */
int func_0010C230(int a0, int a1, int a2);

int func_001030B0(int a0, int a1, int a2) {
    return func_0010C230(a0, a1, a2);
}
