/* asm/cod/003068.s -> func_00103068 @ 0x00103068
 * Tail-call trampoline to sceStdioRead (frame + `j`, the cc=296 shape).
 * The parameter count follows the ps2sdk prototype (UNCONFIRMED for
 * this build); the code is a pure pass-through, so the count does not
 * change the emitted bytes. */
int sceStdioRead(int a0, int a1, int a2);

int func_00103068(int a0, int a1, int a2) {
    return sceStdioRead(a0, a1, a2);
}
