/* asm/cod/003080.s -> func_00103080 @ 0x00103080
 * Tail-call trampoline to sceStdioWrite (frame + `j`, the cc=296 shape).
 * The parameter count follows the ps2sdk prototype (UNCONFIRMED for
 * this build); the code is a pure pass-through, so the count does not
 * change the emitted bytes. */
int sceWrite(int a0, int a1, int a2);

int LoaderSysFWrite(int a0, int a1, int a2) {
    return sceWrite(a0, a1, a2);
}
