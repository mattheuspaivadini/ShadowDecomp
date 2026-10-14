/* asm/cod/003050.s -> func_00103050 @ 0x00103050
 * Tail-call trampoline to sceStdioLseek64 (frame + `j`, the cc=296 shape).
 * The parameter count follows the ps2sdk prototype (UNCONFIRMED for
 * this build); the code is a pure pass-through, so the count does not
 * change the emitted bytes. */
int sceStdioLseek64(int a0, int a1, int a2, int a3);

int func_00103050(int a0, int a1, int a2, int a3) {
    return sceStdioLseek64(a0, a1, a2, a3);
}
