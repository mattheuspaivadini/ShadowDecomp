/* asm/cod/003008.s -> func_00103008 @ 0x00103008
 * Tail-call trampoline to sceStdioOpen (frame + `j`, the cc=296 shape).
 * The parameter count follows the ps2sdk prototype (UNCONFIRMED for
 * this build); the code is a pure pass-through, so the count does not
 * change the emitted bytes. */
int sceStdioOpen(int a0, int a1, int a2);

int func_00103008(int a0, int a1, int a2) {
    return sceStdioOpen(a0, a1, a2);
}
