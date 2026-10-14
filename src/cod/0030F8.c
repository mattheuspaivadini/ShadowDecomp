/* asm/cod/0030F8.s -> func_001030F8 @ 0x001030F8
 * Tail-call trampoline to sceStdioChstat (frame + `j`, the cc=296 shape).
 * The parameter count follows the ps2sdk prototype (UNCONFIRMED for
 * this build); the code is a pure pass-through, so the count does not
 * change the emitted bytes. */
int sceStdioChstat(int a0, int a1, int a2);

int func_001030F8(int a0, int a1, int a2) {
    return sceStdioChstat(a0, a1, a2);
}
