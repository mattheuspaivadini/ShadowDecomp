/* asm/cod/003020.s -> func_00103020 @ 0x00103020
 * Tail-call trampoline to sceStdioClose (frame + `j`, the cc=296 shape).
 * The parameter count follows the ps2sdk prototype (UNCONFIRMED for
 * this build); the code is a pure pass-through, so the count does not
 * change the emitted bytes. */
int sceClose(int a0);

int LoaderSysFClose(int a0) {
    return sceClose(a0);
}
