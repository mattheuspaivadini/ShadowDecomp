/* asm/cod/003008.s -> func_00103008 @ 0x00103008
 * Tail-call trampoline to sceStdioOpen (frame + `j`, the cc=296 shape).
 * The parameter count follows the ps2sdk prototype (UNCONFIRMED for
 * this build); the code is a pure pass-through, so the count does not
 * change the emitted bytes. */
int sceOpen(int a0, int a1, int a2);

int LoaderSysFOpen(int a0, int a1, int a2) {
    return sceOpen(a0, a1, a2);
}
