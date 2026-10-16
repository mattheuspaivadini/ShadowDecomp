/* asm/cod/0289D0.s -> func_001289D0 @ 0x001289D0
 * Tail-call trampoline to func_001120A0 (frame + `j`, the cc=296 shape -
 * same family as the matched func_00103008). Parameter count UNCONFIRMED
 * (pure pass-through; the emitted bytes do not depend on it). */
int getpid(int a0, int a1, int a2);

int _getpid_r(int a0, int a1, int a2) {
    return getpid(a0, a1, a2);
}
