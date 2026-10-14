/* asm/cod/003098.s -> func_00103098 @ 0x00103098
 * Tail-call trampoline to func_0010C058 (frame + `j`, the cc=296 shape -
 * same family as the matched func_00103008). Parameter count UNCONFIRMED
 * (pure pass-through; the emitted bytes do not depend on it). */
int func_0010C058(int a0, int a1, int a2);

int func_00103098(int a0, int a1, int a2) {
    return func_0010C058(a0, a1, a2);
}
