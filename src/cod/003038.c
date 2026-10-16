/* asm/cod/003038.s -> func_00103038 @ 0x00103038
 * Tail-call trampoline to sceStdioLseek (frame + `j`, the cc=296 shape).
 * The parameter count follows the ps2sdk prototype (UNCONFIRMED for
 * this build); the code is a pure pass-through, so the count does not
 * change the emitted bytes. */
int sceLseek(int a0, int a1, int a2);

int LoaderSysFSeek(int a0, int a1, int a2) {
    return sceLseek(a0, a1, a2);
}
